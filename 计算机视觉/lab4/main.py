import tensorflow as tf

model = tf.keras.models.load_model('./tf_vgg16')

model.summary()

input_shape = model.layers[0].input_shape
print("Input shape:", input_shape)

output_shape = model.layers[-1].output_shape
print("Output shape:", output_shape)

model_weights = model.get_weights()
print("Model weights:", model_weights)

loss_function = model.loss
optimizer = model.optimizer
print("Loss function:", loss_function)
print("Optimizer:", optimizer)

model_config = model.get_config()
print("Model configuration:", model_config)