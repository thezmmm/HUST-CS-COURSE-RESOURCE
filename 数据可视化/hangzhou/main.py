import os
import pandas as pd

file_path = './merged_data.csv'

data = pd.read_csv(file_path,encoding='utf-8')

print(data.loc[2])