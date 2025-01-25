import json
from pyecharts import options as opts
from pyecharts.charts import WordCloud

with open('weibo_hot.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

word_cloud_data = []
for key in data:
    word_cloud_data.append((data[key], int(key)*(-1)))

wordcloud = (
    WordCloud(init_opts=opts.InitOpts(width="8000px", height="6000px"))
    .add("", word_cloud_data, word_size_range=[20, 100])
    .set_global_opts(title_opts=opts.TitleOpts(title="微博热搜词云"))
)

wordcloud.render("weibo_hot_wordcloud.html")