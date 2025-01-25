import cv2
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

# 加载模型
model = tf.keras.models.load_model('./tf_vgg16')
model = model.get_layer('vgg16')

# 选择要观察的层的名称或索引
layer_name = 'block5_conv3'  # 替换为您要观察的层的名称或索引

# 获取指定层的输出
layer_output = model.get_layer(layer_name).output

# 创建一个新的模型，该模型的输入是原始模型的输入，输出是指定层的输出
cam_model = tf.keras.models.Model(inputs=model.input, outputs=layer_output)

# 加载图像
image = cv2.imread("./data4/cat.jpg")

# 调整图像大小为224x224像素
image = cv2.resize(image, (224, 224))

# 将图像转换为浮点数并归一化到0到1之间
image = image.astype(np.float32) / 255.0


# 使用新的模型获取指定层的输出（在这种情况下为特征图）
feature_map = cam_model.predict(np.array([image]))
print(feature_map.shape)

# 可视化所有通道的特征图
# for channel in range(feature_map.shape[-1]):
#     plt.figure()
#     plt.imshow(feature_map[0, :, :, channel], cmap='jet')
#     plt.title(f'Channel {channel}')
#     plt.show()

feature_map_channel = 0

# 将特征图叠加到原始图像上
# 将特征图转换为与原始图像相同的数据类型
heatmap = cv2.resize(feature_map[0, :, :, feature_map_channel], (image.shape[1], image.shape[0]))

# 将heatmap映射为RGB图像
heatmap_rgb = np.repeat(heatmap[:, :, np.newaxis], 3, axis=2)

# 将heatmap_rgb和image进行叠加
overlay = cv2.addWeighted(heatmap_rgb, 1, image, 0.3, 0.3)

print(heatmap_rgb.shape)
print(image.shape)
print(type(heatmap_rgb))
print(type(image))

# 显示叠加后的图像
plt.imshow(overlay)
plt.axis('off')
plt.show()