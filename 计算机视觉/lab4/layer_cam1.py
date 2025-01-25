import tensorflow as tf
import numpy as np
import cv2
from matplotlib import pyplot as plt


def layer_cam_analysis(model, image_path, layer_name):
    # 加载图像
    image = cv2.imread(image_path)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    image = image.astype(np.float32) / 255.0

    # 将图像转换为模型期望的输入大小
    image = cv2.resize(image, (224, 224))

    # 将图像转换为模型期望的输入格式
    image = np.expand_dims(image, axis=0)

    # 获取指定层的输出和权重
    layer_output = model.get_layer(layer_name).output
    weights = model.get_layer(layer_name).get_weights()[0]

    # 创建一个新的模型，该模型的输入是原始模型的输入，输出是指定层的输出
    cam_model = tf.keras.models.Model(inputs=model.input, outputs=layer_output)

    # 计算指定层的输出和权重的加权和
    cam_output = cam_model.predict(image)
    cam_output = np.squeeze(cam_output)
    cam_weights = np.mean(weights, axis=(0, 1))
    cam = np.dot(cam_output, cam_weights)
    print(cam_output.shape)
    print(cam_weights.shape)
    print(cam.shape)

    # 对CAM进行归一化
    cam = (cam - np.min(cam)) / (np.max(cam) - np.min(cam))
    cam = cv2.resize(cam, (image.shape[2], image.shape[1]))
    channel_num = cam.shape[-1]
    # 可视化CAM
    heatmap_sum = cv2.resize(cam[:, :, 0], (image.shape[2], image.shape[1]))
    for feature_map_channel in range(1,channel_num):
        heatmap = cv2.resize(cam[:, :, feature_map_channel], (image.shape[2], image.shape[1]))
        heatmap_sum += heatmap
    heatmap_sum_normalized = (heatmap_sum - np.min(heatmap_sum)) / (np.max(heatmap_sum) - np.min(heatmap_sum))
    heatmap = cv2.applyColorMap(np.uint8(255 * heatmap_sum_normalized), cv2.COLORMAP_JET)
    image = image[0]
    heatmap = heatmap.astype(np.float32)
    image = image.astype(np.float32)
    overlay = cv2.addWeighted(heatmap, 0.3, image, 1, 0)
    plt.imshow(overlay)
    plt.show()

# 加载模型
model = tf.keras.models.load_model('./tf_vgg16')
model = model.get_layer('vgg16')

# 图像路径
image_path = './data4/cat.jpg'

# 需要分析的层的名称
layer_name = 'block5_conv3'

# 进行LayerCAM分析
layer_cam_analysis(model, image_path, layer_name)