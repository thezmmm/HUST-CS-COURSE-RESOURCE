import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

# 去重
data = data.drop_duplicates(subset=['小区名称'])

# 绘制散点图
plt.figure(figsize=(10, 8))
plt.scatter(data['经度'], data['纬度'], alpha=0.6)
plt.xlabel('经度')
plt.ylabel('纬度')
plt.title('小区地理分布散点图')
plt.show()

# 绘制热力图
plt.figure(figsize=(10, 8))
sns.kdeplot(data['经度'], data['纬度'], shade=True, cmap='viridis')
plt.xlabel('经度')
plt.ylabel('纬度')
plt.title('小区地理分布热力图')
plt.show()