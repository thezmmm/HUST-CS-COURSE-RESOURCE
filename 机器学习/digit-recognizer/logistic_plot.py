import numpy as np
from matplotlib import pyplot as plt

from logisticRegression import X_test, predictions

num_rows = 4
num_cols = 4

fig, axes = plt.subplots(num_rows, num_cols, figsize=(8, 8))
fig.suptitle('Predictions on Test Set', fontsize=16)
for i in range(num_rows):
    for j in range(num_cols):
        index = i * num_cols + j
        sample = X_test[index]
        label = predictions[index]

        image = sample.reshape(28, 28)

        axes[i][j].imshow(image, cmap='gray')
        axes[i][j].axis('off')
        axes[i][j].set_title(f"Prediction: {label}")

plt.show()