import os
import pandas as pd

# 获取data文件夹下所有CSV文件的文件名
folder_path = 'data/'
csv_files = [file for file in os.listdir(folder_path) if file.endswith('.csv')]

# 创建一个空的DataFrame用于存储合并的结果
merged_data = pd.DataFrame()

# 遍历每个CSV文件并进行合并
for file in csv_files:
    # 读取CSV文件
    file_path = os.path.join(folder_path, file)
    data = pd.read_csv(file_path,encoding='GBK')

    # 添加文件名列
    print(file)
    data['区域'] = file[0:-9]

    # 将当前CSV文件的数据合并到结果DataFrame中
    merged_data = pd.concat([merged_data, data], ignore_index=True)

# 将合并结果保存为新的CSV文件
merged_data.to_csv('merged_data.csv', index=False,encoding='utf-8')