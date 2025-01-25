import pandas as pd
import matplotlib.pyplot as plt

# 读取Excel文件
data = pd.ExcelFile('covid19_data.xls').parse('data_history')
print(data)
# 提取所需的列数据
dates = data['date']
confirm = data['confirm']
dead = data['dead']
heal = data['heal']

# 创建折线图
plt.figure(figsize=(10, 6))  # 设置图形大小
plt.plot(dates, confirm, marker='o', linestyle='-', color='blue', label='Confirm')  # 绘制confirm折线
plt.plot(dates, dead, marker='s', linestyle='--', color='red', label='Dead')  # 绘制dead折线
plt.plot(dates, heal, marker='^', linestyle=':', color='green', label='Heal')  # 绘制heal折线

plt.xlabel('Date')  # 设置x轴标签
plt.xticks(range(0,len(dates),5))
plt.ylabel('Count')  # 设置y轴标签
plt.title('COVID-19 Data')  # 设置图表标题
plt.legend()  # 显示图例
plt.grid(True)  # 显示网格线

# 创建散点图
plt.figure(figsize=(10, 6))  # 设置图形大小
plt.scatter(dates, confirm, marker='o', color='blue', label='Confirm')  # 绘制confirm散点
plt.scatter(dates, dead, marker='s', color='red', label='Dead')  # 绘制dead散点
plt.scatter(dates, heal, marker='^', color='green', label='Heal')  # 绘制heal散点

plt.xlabel('Date')  # 设置x轴标签
plt.xticks(range(0,len(dates),5))
plt.ylabel('Count')  # 设置y轴标签
plt.title('COVID-19 Data')  # 设置图表标题
plt.legend()  # 显示图例
plt.grid(True)  # 显示网格线

# 显示图表
plt.show()