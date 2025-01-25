import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]

# 读取Excel文件
xls_path = 'covid19_data.xls'
xls_file = pd.ExcelFile(xls_path)

# 读取data_world工作表数据
df = xls_file.parse('data_world')

# 按确诊人数降序排序
df_sorted = df.sort_values(by='confirm', ascending=False)

# 获取前4个国家的数据
top_countries = df_sorted.head(4)

# 创建一个4x4的子图布局
fig, axs = plt.subplots(2, 2, figsize=(10, 10))

# 遍历每个国家，绘制饼图
for i, country in enumerate(top_countries['country']):
    confirm = top_countries.iloc[i]['confirm']
    dead = top_countries.iloc[i]['dead']
    heal = top_countries.iloc[i]['heal']
    suspect = top_countries.iloc[i]['suspect']

    # 绘制饼图
    labels = ['Confirm', 'Dead', 'Heal', 'Suspect']
    data = [confirm, dead, heal, suspect]

    # 计算子图的行列索引
    row = i // 2
    col = i % 2

    axs[row, col].pie(data, labels=labels, autopct='%1.1f%%')
    axs[row, col].set_title(f'{country} COVID-19 Cases Distribution')

plt.tight_layout()
plt.show()