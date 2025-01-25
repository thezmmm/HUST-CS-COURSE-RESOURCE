import pandas as pd
import folium
from folium.plugins import HeatMap

# 读取数据
data = pd.read_csv('./merged_data.csv')

# 去重
data = data.drop_duplicates(subset=['小区名称'])

# 创建地图
m = folium.Map(location=[data['纬度'].mean(), data['经度'].mean()], zoom_start=10)

# 绘制散点图
for _, row in data.iterrows():
    folium.CircleMarker(location=[row['纬度'], row['经度']], radius=5, color='blue', fill=True).add_to(m)

# 绘制热力图
heat_data = [[row['纬度'], row['经度'], row['关注度']] for _, row in data.iterrows()]
HeatMap(heat_data).add_to(m)

# 保存地图
m.save('map.html')