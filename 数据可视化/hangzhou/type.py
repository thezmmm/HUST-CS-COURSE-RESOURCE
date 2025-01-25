import pandas as pd
import matplotlib.pyplot as plt
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

# 统计建筑类型的计数
building_counts = data['建筑类型'].value_counts()

# 绘制建筑情况的条形图
plt.figure(figsize=(8, 6))
building_counts.plot(kind='bar')
plt.xlabel('建筑类型')
plt.ylabel('数量')
plt.title('建筑类型条形图')
plt.show()

# 绘制装修类型的饼图
plt.figure(figsize=(8, 8))
building_counts.plot(kind='pie', autopct='%1.1f%%')
plt.axis('equal')
plt.title('建筑类型饼图')
plt.legend()
plt.show()

# 统计装修情况的计数
decoration_counts = data['装修情况'].value_counts()

# 绘制建筑情况的条形图
plt.figure(figsize=(8, 6))
decoration_counts.plot(kind='bar')
plt.xlabel('装修情况')
plt.ylabel('数量')
plt.title('装修情况条形图')
plt.show()

# 绘制装修类型的饼图
plt.figure(figsize=(8, 8))
decoration_counts.plot(kind='pie', autopct='%1.1f%%')
plt.axis('equal')
plt.title('装修情况饼图')
plt.legend()
plt.show()