import cv2
import numpy as np
import tensorflow as tf

# 读取JPEG图像文件
image = cv2.imread("./data4/cat1.jpg")

# 调整图像大小为224x224像素
image = cv2.resize(image, (224, 224))

# 将图像转换为浮点数并归一化到0到1之间
image = image.astype(np.float32) / 255.0

# 添加一个额外的维度以匹配模型的输入形状
image = np.expand_dims(image, axis=0)

# 打印处理后的图像形状
print("Processed image shape:", image.shape)

model = tf.keras.models.load_model('./tf_vgg16')

# 使用模型进行预测
predictions = model.predict(image)
# 解析预测结果
predicted_class_index = np.argmax(predictions[0])
confidence = predictions[0, predicted_class_index]

# 打印预测结果
print(predictions)
print(predicted_class_index)
print("Confidence:", confidence)