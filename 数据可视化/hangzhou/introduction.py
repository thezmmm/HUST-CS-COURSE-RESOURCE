import pandas as pd
from wordcloud import WordCloud
import jieba
import matplotlib.pyplot as plt

from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Microsoft YaHei'] # 指定默认字体：解决plot不能显示中文问题
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

# 读取数据
data = pd.read_csv('./merged_data.csv')

# 将小区介绍和周边配套的文本数据合并
data['小区介绍'] = data['小区介绍'].fillna('')  # 处理小区介绍列中的缺失值
data['周边配套'] = data['周边配套'].fillna('')  # 处理周边配套列中的缺失值
data['核心卖点'] = data['核心卖点'].fillna('')  # 处理核心卖点列中的缺失值
text_data = data['小区介绍'] + ' ' + data['周边配套'] + ' ' + data['核心卖点']

# 文本分词处理
text_seg = ' '.join(jieba.cut(' '.join(text_data)))

# 生成文字云图
wordcloud = WordCloud(width=800, height=400, background_color='white', font_path='C:\Windows\Fonts\msyh.ttc', collocations=False).generate(text_seg)

# 显示文字云图
plt.figure(figsize=(10, 6))
plt.imshow(wordcloud, interpolation='bilinear')
plt.axis('off')
plt.title('房屋介绍文字云图')
plt.show()