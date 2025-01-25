import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

def layer_cam(model, target_layer, input_image, target_class):
    # Create a sub-model that outputs the target layer activations and gradients
    sub_model = tf.keras.models.Model(inputs=model.inputs, outputs=[target_layer.output, model.output])

    # Forward pass
    with tf.GradientTape() as tape:
        target_layer_output,predictions = sub_model(input_image, training=False)
        print(target_layer_output.shape)
        target_activation = target_layer_output[:, target_class]
        loss = tf.reduce_mean(target_activation)

    # Get the gradients of the target layer with respect to the loss
    gradients = tape.gradient(loss, target_layer_output)

    # Compute the weights as ReLU of the gradients
    weights = tf.nn.relu(gradients)

    # Compute the importance map by element-wise multiplication of weights and target layer activations
    importance_map = tf.reduce_sum(tf.multiply(weights, target_layer_output), axis=-1)

    # Normalize the importance map
    importance_map /= tf.reduce_max(importance_map)

    return importance_map.numpy()[0]

# 加载模型
model = tf.keras.models.load_model('./tf_vgg16')
model = model.get_layer("vgg16")

# Choose the target layer (e.g., the last convolutional layer)
target_layer = model.get_layer('block5_conv3')

# Load and preprocess the input image
input_image = tf.keras.preprocessing.image.load_img('./data4/both.jpg', target_size=(224, 224))
input_image = tf.keras.preprocessing.image.img_to_array(input_image)
input_image = np.expand_dims(input_image, axis=0)
input_image = tf.keras.applications.resnet50.preprocess_input(input_image)

# Generate the heatmap for a specific target class (e.g., class index 7)
heatmap = layer_cam(model, target_layer, input_image, 7)

# Plot the heatmap
plt.imshow(heatmap, cmap='jet')
plt.axis('off')
plt.show()