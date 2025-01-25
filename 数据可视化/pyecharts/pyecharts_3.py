import pandas as pd
from pyecharts import options as opts
from pyecharts.charts import Bar, Pie, Line

# 读取数据文件
data = pd.read_excel('student.xls')

# 处理缺考和作弊情况，将分数中的缺考和作弊替换为0
data.replace('缺考', 0, inplace=True)
data.replace('作弊', 0, inplace=True)

# 1. 条形图显示所有学生的总分
total_scores = data[['英语', '体育', '军训', '数分', '高代', '解几']].sum(axis=1)
bar = (
    Bar()
    .add_xaxis(data['姓名'].tolist())
    .add_yaxis('总分', total_scores.tolist())
    .set_global_opts(
        title_opts=opts.TitleOpts(title="所有学生的总分条形图"),
        xaxis_opts=opts.AxisOpts(axislabel_opts=opts.LabelOpts(rotate=-45))
    )
)
bar.render("total_scores_bar.html")

# 2. 饼图展示总分前3名的分数构成
# 获取总分列
data['总分'] = data[['英语', '体育', '军训', '数分', '高代', '解几']].sum(axis=1)

# 获取总分前三名的数据
top3 = data.nlargest(3, '总分')

# 遍历每个总分前三名的学生
for _, row in top3.iterrows():
    # 获取学生姓名和各科目分数
    name = row['姓名']
    scores = row[['英语', '体育', '军训', '数分', '高代', '解几']]

    # 创建饼图
    pie = (
        Pie()
            .add("", [list(z) for z in zip(scores.index, scores)])
            .set_global_opts(title_opts=opts.TitleOpts(title=f"{name}的分数构成"))
            .set_series_opts(label_opts=opts.LabelOpts(formatter="{b}: {c}"))
    )

    # 保存图表到HTML文件
    pie.render(f"{name}_pie_chart.html")

# 3. 折线图显示英语、数分、高代、解几四门课程的成绩分布
# 统计每门课程分数段的人数
score_ranges = range(0, 101, 10)
english_scores = [len(data[(data['英语'] >= start) & (data['英语'] < start + 10)]) for start in score_ranges]
math_scores = [len(data[(data['数分'] >= start) & (data['数分'] < start + 10)]) for start in score_ranges]
calculus_scores = [len(data[(data['高代'] >= start) & (data['高代'] < start + 10)]) for start in score_ranges]
physics_scores = [len(data[(data['解几'] >= start) & (data['解几'] < start + 10)]) for start in score_ranges]

# 创建折线图
line_chart = (
    Line()
    .add_xaxis([str(start) + '-' + str(start + 10) for start in score_ranges])
    .add_yaxis('英语', english_scores)
    .add_yaxis('数分', math_scores)
    .add_yaxis('高代', calculus_scores)
    .add_yaxis('解几', physics_scores)
    .set_global_opts(
        title_opts=opts.TitleOpts(title='成绩分布图'),
        xaxis_opts=opts.AxisOpts(name='分数段'),
        yaxis_opts=opts.AxisOpts(name='人数'),
    )
)

# 生成HTML文件
line_chart.render('subject_scores_line.html')

# 4. 可视化展示男生和女生各科平均成绩的对比
subjects = ['英语', '数分', '高代', '解几']
data['英语'] = data['英语'].astype(float)  # 将英语成绩列转换为浮点型
gender_avg_scores = data.groupby('性别')[subjects + ['体育', '军训']].mean()  # 平均成绩计算包括体育和军训
bar_gender = (
    Bar()
    .add_xaxis(gender_avg_scores.columns.tolist())
    .add_yaxis('男生', gender_avg_scores.loc['男'].tolist())
    .add_yaxis('女生', gender_avg_scores.loc['女'].tolist())
    .set_global_opts(title_opts=opts.TitleOpts(title="男生和女生各科平均成绩对比"))
)
bar_gender.render("gender_avg_scores_bar.html")