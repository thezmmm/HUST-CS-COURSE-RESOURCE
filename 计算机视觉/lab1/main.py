import pandas as pd
import numpy as np
import tensorflow as tf
from sklearn.model_selection import train_test_split

num_layers = 3
num_neurons = 100
activation_function = 'relu'

# 加载数据集
data = pd.read_csv('dataset.csv')

# 随机排序数据集
data = data.sample(frac=1).reset_index(drop=True)

# 提取特征和标签
features = data[['data1', 'data2']].values
labels = data['label'].values - 1

# 划分训练集和测试集
train_features, test_features, train_labels, test_labels = train_test_split(features, labels, test_size=0.1, random_state=42)

# 定义神经网络的架构
model = tf.keras.Sequential([
    tf.keras.layers.Dense(64, activation=activation_function, input_shape=(2,)),
    tf.keras.layers.Dense(32, activation=activation_function),
    tf.keras.layers.Dense(4, activation='softmax')
])

# 保存模型结构为TensorBoard日志文件
log_dir = "logs/layers_{}_neurons_{}_activation_{}".format(num_layers, num_neurons, activation_function)
tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)

# 编译和训练模型
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
model.fit(train_features, train_labels, epochs=10, batch_size=32, callbacks=[tensorboard_callback])

# 评估模型性能
_, test_accuracy = model.evaluate(test_features, test_labels)
print('Test Accuracy:', test_accuracy)