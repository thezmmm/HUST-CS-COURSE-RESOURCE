# 在测试集上验证模型并可视化展示部分预测结果
import numpy as np
from matplotlib import pyplot as plt
from nn import X_test, test_data, model

num_samples = 16
sample_indices = np.random.choice(len(test_data), num_samples)

fig, axes = plt.subplots(nrows=4, ncols=4, figsize=(8, 8))
fig.suptitle('Predictions on Test Set', fontsize=16)

for i, ax in enumerate(axes.flat):
    index = sample_indices[i]
    img = X_test[index].reshape(28, 28)
    ax.imshow(img, cmap='gray')
    ax.axis('off')
    pred = model.predict(X_test[index].reshape(1, -1))[0]
    ax.set_title(f'Pred: {pred}')

plt.show()