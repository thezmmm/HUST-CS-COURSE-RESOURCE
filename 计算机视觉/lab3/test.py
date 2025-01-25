import tensorflow as tf
from sklearn.model_selection import train_test_split
import numpy as np

# 加载MNIST数据集
(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.mnist.load_data()

# 将像素值缩放到0到1之间
train_images = train_images / 255.0
test_images = test_images / 255.0

# 将训练集和测试集分割为10%的数据
train_images, _, train_labels, _ = train_test_split(train_images, train_labels, train_size=0.9, stratify=train_labels)
test_images, _, test_labels, _ = train_test_split(test_images, test_labels, train_size=0.9, stratify=test_labels)


# 构建用于本次实验的训练集和测试集
def create_dataset(images, labels):
    num_samples = len(images)
    combined_images = []
    combined_labels = []

    for i in range(num_samples):
        # 随机选择另一张图片
        other_index = np.random.choice(num_samples)
        while other_index == i:
            other_index = np.random.choice(num_samples)

        # 将两张图片合并
        combined_image = np.concatenate([images[i], images[other_index]], axis=1)
        combined_images.append(combined_image)

        # 判断是否为同一个数字
        is_same_digit = int(labels[i] == labels[other_index])
        combined_labels.append(is_same_digit)

    combined_images = np.array(combined_images)
    combined_labels = np.array(combined_labels)

    return combined_images, combined_labels


# 创建训练集和测试集
train_images, train_labels = create_dataset(train_images, train_labels)
test_images, test_labels = create_dataset(test_images, test_labels)

# 打印训练集和测试集的形状
print("训练集形状:", train_images.shape, train_labels.shape)
print("测试集形状:", test_images.shape, test_labels.shape)

from tensorflow.keras import layers, models

# 构建卷积神经网络模型
model = models.Sequential()
model.add(layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 56, 1)))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(64, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Flatten())
model.add(layers.Dense(64, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

# 编译模型
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# 将训练集形状调整为适应模型
train_images = np.expand_dims(train_images, axis=-1)

# 训练模型
model.fit(train_images, train_labels, epochs=10, batch_size=32)

# 在测试集上评估模型性能
test_images = np.expand_dims(test_images, axis=-1)
test_loss, test_accuracy = model.evaluate(test_images, test_labels)
print("测试集损失:", test_loss)
print("测试集准确率:", test_accuracy)