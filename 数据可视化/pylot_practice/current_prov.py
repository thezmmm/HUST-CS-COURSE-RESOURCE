import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]

# 读取Excel文件中的工作表
data = pd.read_excel('covid19_data.xls', sheet_name='current_prov')

df = pd.DataFrame(data)

# 创建子图
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))

# 绘制条形图
ax1.bar(df['province'], df['confirm'], label='confirm', color='blue')
ax1.bar(df['province'], df['dead'], label='dead', color='red')
ax1.bar(df['province'], df['heal'], label='heal', color='green')
ax1.set_ylabel('Count')
ax1.set_title('COVID-19 Data by Province')
ax1.legend()

# 绘制直方图
ax2.hist(df['confirm'], bins=10, alpha=0.5, label='confirm', color='blue')
ax2.hist(df['dead'], bins=10, alpha=0.5, label='dead', color='red')
ax2.hist(df['heal'], bins=10, alpha=0.5, label='heal', color='green')
ax2.set_xlabel('Count')
ax2.set_ylabel('Frequency')
ax2.set_title('Histogram of COVID-19 Data')
ax2.legend()

# 调整子图之间的间距
plt.tight_layout()

# 显示图形
plt.show()