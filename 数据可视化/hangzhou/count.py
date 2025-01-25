import pandas as pd
import matplotlib.pyplot as plt

from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

data_region = data.groupby("区域").size()

# 绘制饼图
plt.figure(figsize=(12, 12))
data_region.plot(kind='pie', autopct='%.1f%%')
plt.ylabel('')
plt.title('各区域房屋数量占比')
plt.show()


# 获取区域位置
locations = data.groupby("区域")["区域位置"].value_counts()
# 获取所有的区域
regions = data["区域"].unique()

# 遍历每个区域，并绘制饼图
for region in regions:
    region_data = locations[region]

    # 绘制饼图
    plt.figure(figsize=(12, 12))
    region_data.plot(kind='pie', autopct='%.1f%%')
    plt.ylabel('')
    plt.title(f'{region}区域下各区域位置房屋数量占比')
    plt.show()