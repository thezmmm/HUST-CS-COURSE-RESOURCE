import numpy as np
import pandas as pd
import csv

from matplotlib import pyplot as plt

train_df = pd.read_csv("./data/train.csv")
test_df = pd.read_csv("./data/test.csv")

X_train = train_df.iloc[:, 1:].values / 255.0
y_train = train_df.iloc[:, 0].values
X_test = test_df.values / 255.0

def logistic_regression(X, y, alpha=0.1, lambda_reg=0.1, num_iters=100):
    m, n = X.shape
    theta = np.zeros(n)
    for i in range(num_iters):
        h = sigmoid(np.dot(X, theta))
        gradient = np.dot(X.T, (h - y)) + lambda_reg * theta
        gradient[0] -= lambda_reg * theta[0]
        theta -= alpha * gradient / m
    return theta

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

k = 10
all_theta = np.zeros((k, X_train.shape[1]))
for i in range(k):
    y_i = np.array([1 if label == i else 0 for label in y_train])
    all_theta[i] = logistic_regression(X_train, y_i)

predictions = []
for i in range(len(X_test)):
    h_i = [sigmoid(np.dot(all_theta[j], X_test[i])) for j in range(k)]
    label_i = np.argmax(h_i)
    predictions.append(label_i)

image_ids = range(1, len(predictions) + 1)

with open('./data/predictions.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['ImageId', 'Label'])
    for image_id, label in zip(image_ids, predictions):
        writer.writerow([image_id, label])
