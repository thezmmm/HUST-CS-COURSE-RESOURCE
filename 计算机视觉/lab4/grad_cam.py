import tensorflow as tf
from tf_explain.core.grad_cam import GradCAM
import cv2
import numpy as np

# 加载模型
model = tf.keras.models.load_model('./tf_vgg16')
model = model.get_layer("vgg16")

# 选择要解释的图像
image_path = "./data4/dog1.jpg"

# 加载图像并进行预处理
image = cv2.imread(image_path)
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
image = cv2.resize(image, (224, 224))
image = np.expand_dims(image, axis=0)

# 创建Grad-CAM对象并进行解释
explainer = GradCAM()
for channel_index in range(7):
    grid = explainer.explain((image, 'dog'), model, layer_name="block5_conv3", class_index=channel_index,image_weight=0.1)

    # 可视化Grad-CAM结果
    explainer.save(grid, "./grad_cam/dog", "grad_cam_{}.jpg".format(channel_index))