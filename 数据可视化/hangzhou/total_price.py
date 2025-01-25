import pandas as pd
import matplotlib.pyplot as plt
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

file_path = './merged_data.csv'

data = pd.read_csv(file_path,encoding='utf-8')


# 计算每个区域的总价中位数
median_prices = data.groupby('区域')['总价'].median()

# 绘制直方图
plt.figure(figsize=(10, 6))
median_prices.plot(kind='bar')
plt.xlabel('区域')
plt.ylabel('总价中位数')
plt.title('每个区域的总价中位数直方图')
plt.xticks(rotation=45)
plt.show()

median_prices = data.groupby(['区域', '区域位置'])['总价'].median().reset_index()

unique_regions = median_prices['区域'].unique()
num_regions = len(unique_regions)

num_cols = 3  # 每行显示的子图数量
num_rows = (num_regions - 1) // num_cols + 1  # 计算行数

fig, axes = plt.subplots(nrows=num_rows, ncols=num_cols, figsize=(15, 5*num_rows))

# 计算纵轴范围
max_price = median_prices['总价'].max()
min_price = median_prices['总价'].min()

for i, region in enumerate(unique_regions):
    region_data = median_prices[median_prices['区域'] == region]
    row = i // num_cols
    col = i % num_cols
    ax = axes[row][col]
    ax.bar(region_data['区域位置'], region_data['总价'])
    ax.set_xlabel('区域位置')
    ax.set_ylabel('总价中位数')
    ax.set_title(f'{region}区域位置的总价中位数')
    ax.tick_params(axis='x', rotation=45)
    ax.set_ylim(min_price, max_price)  # 统一纵轴范围

# 隐藏多余的子图
if num_regions < num_rows * num_cols:
    for i in range(num_regions, num_rows*num_cols):
        row = i // num_cols
        col = i % num_cols
        fig.delaxes(axes[row][col])

plt.tight_layout()
plt.show()