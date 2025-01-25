import pandas as pd
import matplotlib.pyplot as plt

from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

grouped = data["户型结构"].value_counts()
grouped = grouped.drop("暂无数据", errors='ignore')

# 绘制柱状图
plt.figure(figsize=(8, 6))
grouped.plot(kind='bar')
plt.xlabel('户型结构')
plt.ylabel('数量')
plt.title('不同户型结构的数量')

plt.show()

# 绘制饼图
plt.figure(figsize=(12, 12))
grouped.plot(kind='pie', autopct='%.1f%%')
plt.ylabel('')
plt.title('不同户型结构的数量')
plt.show()


grouped = data["房屋户型"].value_counts()
# 将数量低于100的房屋户型合并为"其他"
threshold = 100
other_count = grouped[grouped <= threshold].sum()
grouped = grouped[grouped >= threshold]
grouped['其他'] = other_count


# 绘制柱状图
plt.figure(figsize=(12, 12))
grouped.plot(kind='bar')
plt.xlabel('房屋户型')
plt.ylabel('数量')
plt.title('不同房屋户型的数量')

plt.show()

# 绘制饼图
plt.figure(figsize=(8, 8))
grouped.plot(kind='pie', autopct='%.1f%%')
plt.ylabel('')
plt.title('不同房屋户型的数量')
plt.show()