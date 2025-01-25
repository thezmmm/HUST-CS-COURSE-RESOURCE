import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import seaborn as sns
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

# 绘制散点图
plt.figure(figsize=(10, 8))
sns.scatterplot(data=data, x='经度', y='纬度', size='关注度', sizes=(20, 200), alpha=0.7)
plt.title('位置与关注度散点图')
plt.show()

# 绘制热力图
sns.kdeplot(data=data, x='经度', y='纬度', weights='关注度', cmap='hot', shade=True)
plt.title('热力图')
plt.show()