import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from pylab import mpl
from sklearn.preprocessing import PolynomialFeatures

mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

# 去除建筑面积和套内面积字段中的单位和暂无数据
data['建筑面积'] = data['建筑面积'].str.replace('㎡', '')
data['套内面积'] = data['套内面积'].str.replace('㎡', '')
data = data[data['建筑面积'] != '暂无数据']
data = data[data['套内面积'] != '暂无数据']
data['建筑面积'] = pd.to_numeric(data['建筑面积'])
data['套内面积'] = pd.to_numeric(data['套内面积'])
data = data.dropna(subset=['套内面积', '建筑面积'])

x = data['建筑面积'].values.reshape(-1, 1)
y = data['套内面积'].values.reshape(-1, 1)

# 多项式特征转换
poly_features = PolynomialFeatures(degree=2)  # 设置多项式的阶数
x_poly = poly_features.fit_transform(x)

# 多项式回归模型训练
model = LinearRegression()
model.fit(x_poly, y)

# 预测并绘制曲线
x_pred = np.linspace(x.min(), x.max(), 100).reshape(-1, 1)
x_pred_poly = poly_features.transform(x_pred)
y_pred = model.predict(x_pred_poly)

plt.scatter(x, y)
plt.plot(x_pred, y_pred, color='red', linewidth=2)
plt.xlabel('建筑面积')
plt.ylabel('套内面积')
plt.title('建筑面积与套内面积多项式回归拟合')
plt.show()