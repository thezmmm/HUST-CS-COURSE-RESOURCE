import numpy as np
import pandas as pd

# 读取训练集数据
train_data = pd.read_csv("./data/train.csv")

# 分割训练集和验证集
train_size = int(len(train_data) * 0.8)
train_set = train_data[:train_size]
val_set = train_data[train_size:]

# 归一化像素值到0~1之间
X_train = train_set.iloc[:, 1:].values.astype('float32') / 255.0
y_train = train_set.iloc[:, 0].values.astype('int32')
X_val = val_set.iloc[:, 1:].values.astype('float32') / 255.0
y_val = val_set.iloc[:, 0].values.astype('int32')


# 定义一个简单的神经网络模型
class NeuralNetwork:
    def __init__(self):
        self.w = np.random.rand(784, 10)
        self.b = np.random.rand(10)

    def softmax(self, z):
        return np.exp(z) / np.sum(np.exp(z), axis=1, keepdims=True)

    def cross_entropy(self, y_pred, y_true):
        m = y_pred.shape[0]
        log_likelihood = -np.log(y_pred[range(m), y_true])
        loss = np.sum(log_likelihood) / m
        return loss

    def predict(self, X):
        z = np.dot(X, self.w) + self.b
        y_prob = self.softmax(z)
        return np.argmax(y_prob, axis=1)

    def train(self, X, y, lr=0.1):
        z = np.dot(X, self.w) + self.b
        y_pred = self.softmax(z)
        grad_w = np.dot(X.T, (y_pred - y))
        grad_b = np.sum(y_pred - y, axis=0)
        self.w -= lr * grad_w
        self.b -= lr * grad_b


# 训练神经网络模型
model = NeuralNetwork()
epochs = 10

for i in range(epochs):
    for j in range(len(train_set)):
        x = X_train[j]
        y = np.zeros(10)
        y[y_train[j]] = 1

        model.train(x.reshape(1, -1), y.reshape(1, -1))

# 验证模型并保存结果到csv文件中
test_data = pd.read_csv("./data/test.csv")
X_test = test_data.values.astype('float32') / 255.0
y_pred = model.predict(X_test)

results = pd.DataFrame({'ImageId': range(1, len(test_data) + 1), 'Label': y_pred})
results.to_csv('./data/submission.csv', index=False)