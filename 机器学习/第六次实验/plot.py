import matplotlib.pyplot as plt

# 从文件中读取数据
with open('mnist.txt', 'r') as f:
    lines = f.readlines()

# 解析每一行数据，提取loss值
losses = []
for line in lines:
    if 'loss is' in line:
        loss = float(line.split('loss is ')[1])
        losses.append(loss)

# 绘制曲线图
plt.plot(losses)
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.title('Loss Curve')
plt.show()
