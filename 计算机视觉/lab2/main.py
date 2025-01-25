import tensorflow as tf
from tensorflow.keras import layers
from tensorflow.keras.callbacks import TensorBoard

activation_function = "ReLU"

# 自定义指标,查看每个类别的准确度
class PerClassAccuracy(tf.keras.callbacks.Callback):
    def __init__(self, validation_data):
        super(PerClassAccuracy, self).__init__()
        self.validation_data = validation_data

    def on_epoch_end(self, epoch, logs=None):
        # 预测验证集数据
        predictions = self.model.predict(self.validation_data[0])
        predicted_labels = tf.argmax(predictions, axis=1)

        # 计算每个类别的准确度
        num_classes = len(tf.unique(self.validation_data[1])[0])
        class_accuracy = []
        for class_id in range(num_classes):
            class_indices = tf.where(tf.equal(self.validation_data[1], class_id))
            class_labels = tf.gather(self.validation_data[1], class_indices)
            class_predictions = tf.gather(predicted_labels, class_indices)

            # 将class_labels和class_predictions转换为int64类型
            class_labels = tf.cast(class_labels, tf.int64)
            class_predictions = tf.cast(class_predictions, tf.int64)

            accuracy = tf.reduce_mean(tf.cast(tf.equal(class_labels, class_predictions), tf.float32))
            class_accuracy.append(accuracy)

        # 将每个类别的准确度添加到日志中
        for class_id, accuracy in enumerate(class_accuracy):
            logs[f'val_accuracy_class_{class_id}'] = accuracy

def resnet_block(x, filters, downsample=False):
    identity = x

    # 第一个卷积层
    x = layers.Conv2D(filters, kernel_size=(3, 3), strides=(1 if not downsample else 2, 1 if not downsample else 2), padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation(activation_function)(x)

    # 第二个卷积层
    x = layers.Conv2D(filters, kernel_size=(3, 3), strides=(1, 1), padding='same')(x)
    x = layers.BatchNormalization()(x)

    # 如果下采样，使用1x1卷积进行维度匹配
    if downsample:
        identity = layers.Conv2D(filters, kernel_size=(1, 1), strides=(2, 2), padding='same')(identity)
        identity = layers.BatchNormalization()(identity)

    # 残差连接
    x = layers.Add()([x, identity])
    x = layers.Activation(activation_function)(x)

    return x

def build_model():
    inputs = tf.keras.Input(shape=(28, 28, 1))

    # 第一个卷积层
    x = layers.Conv2D(64, kernel_size=(7, 7), strides=(2, 2), padding='same')(inputs)
    x = layers.BatchNormalization()(x)
    x = layers.Activation(activation_function)(x)
    x = layers.MaxPooling2D(pool_size=(3, 3), strides=(2, 2), padding='same')(x)

    # 使用ResNet模块构建网络
    x = resnet_block(x, filters=64)
    x = resnet_block(x, filters=64)
    x = resnet_block(x, filters=64)

    x = layers.GlobalAveragePooling2D()(x)

    # 全连接层
    x = layers.Dense(64, activation=activation_function)(x)
    outputs = layers.Dense(10, activation='softmax')(x)

    model = tf.keras.Model(inputs=inputs, outputs=outputs)
    return model

model = build_model()

lr = 0.001
optimizer = tf.keras.optimizers.Adam(learning_rate=lr)  # 优化器和学习率
# optimizer = tf.keras.optimizers.RMSprop(learning_rate=lr)
# optimizer = tf.keras.optimizers.SGD(learning_rate=lr)
loss_function = tf.keras.losses.SparseCategoricalCrossentropy() # 损失函数
# loss_function = tf.keras.losses.BinaryCrossentropy()
# loss_function=tf.keras.losses.MeanSquaredError()
batch_size = 64  # 批量大小
epochs = 10  # 训练周期

# 编译模型
model.compile(optimizer=optimizer,
              loss=loss_function,
              metrics=['accuracy'])

# 加载MNIST数据集
(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.mnist.load_data()

# 对数据进行归一化和维度调整
train_images = train_images.reshape(-1, 28, 28, 1).astype('float32') / 255.0
test_images = test_images.reshape(-1, 28, 28, 1).astype('float32') / 255.0

# 定义TensorBoard回调函数
log_dir = "logs/batchsize_{}_optimizer_{}_loss_{}_activation_{}_lr_{}".format(batch_size,optimizer.name,loss_function.name ,activation_function,lr) # 设置日志保存路径
tensorboard_callback = TensorBoard(log_dir=log_dir, histogram_freq=1)
per_class_accuracy_callback = PerClassAccuracy(validation_data=(test_images, test_labels))

# 训练模型
model.fit(train_images, train_labels, batch_size=batch_size, epochs=epochs,
          validation_data=(test_images, test_labels),
          callbacks=[tensorboard_callback,per_class_accuracy_callback])