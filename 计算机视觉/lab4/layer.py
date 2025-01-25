import tensorflow as tf
from keras import Model
import cv2
import numpy as np

# 读取JPEG图像文件
image = cv2.imread("./data4/both.jpg")

# 调整图像大小为224x224像素
image = cv2.resize(image, (224, 224))

# 将图像转换为浮点数并归一化到0到1之间
image = image.astype(np.float32) / 255.0

# 添加一个额外的维度以匹配模型的输入形状
input_data = np.expand_dims(image, axis=0)

model = tf.keras.models.load_model('./tf_vgg16')

vgg16_layer = model.get_layer("vgg16")

print("last conv layer shape: ",vgg16_layer.get_layer('block5_conv3').kernel.shape)

layer_names = [layer.name for layer in vgg16_layer.layers]
print(layer_names)

outputs = [vgg16_layer.get_layer(layer_name).output for layer_name in layer_names]

intermediate_model = Model(inputs=vgg16_layer.input, outputs=outputs)

intermediate_outputs = intermediate_model.predict(input_data)

print(intermediate_outputs)

for intermediate_output in intermediate_outputs:
    print(intermediate_output.shape)

# 选择要显示的通道索引（这里选择第一个通道）
channel_index = 0


import matplotlib.pyplot as plt
import math

for i, output in enumerate(intermediate_outputs):
    # 获取输出的形状
    output_shape = output.shape

    # 如果输出是 4 维的，假设为 (batch_size, height, width, channels)
    # 这里假设 batch_size = 1，所以可以忽略第一个维度
    feature_maps = output[0]

    # 可视化每个通道的特征图
    num_channels = output_shape[-1]

    # 计算合适的布局
    rows = math.ceil(math.sqrt(num_channels))
    cols = math.ceil(num_channels / rows)

    fig, axs = plt.subplots(rows, cols, figsize=(12, 12))

    # 展示特征图
    for j, ax in enumerate(axs.flat):
        if j < num_channels:
            ax.imshow(feature_maps[:, :, j])
            ax.axis('off')
        else:
            ax.axis('off')

    plt.suptitle(f"Block {i + 1} - {layer_names[i]}")
    plt.show()
