## database table building

### user

- user_id -key   string
- user_name     string
- password     string
- level     int
- register_date  Date
- login_date    Date

## user posts

- user_id
- post_id

## post

- post_id -key  string
- post_title
- post_content
- post_date
- like

## comment

- comment_id
- post_id
- comment_content
- comment_date
- like



```mysql
-- 创建user表，存储用户信息
CREATE TABLE user (
  user_id VARCHAR(50) PRIMARY KEY, -- 用户ID，作为主键
  user_name VARCHAR(50), -- 用户名
  password VARCHAR(50), -- 密码
  level INT, -- 用户级别
  register_date DATE, -- 注册日期
  login_date DATE -- 登录日期
);

-- 创建user_posts表，存储用户和帖子的关联关系
CREATE TABLE user_posts (
  user_id VARCHAR(50), -- 用户ID，作为外键
  post_id VARCHAR(50), -- 帖子ID，作为外键
  PRIMARY KEY (user_id, post_id) -- 设置联合主键
);

-- 创建post表，存储帖子信息
CREATE TABLE post (
  post_id VARCHAR(50) PRIMARY KEY, -- 帖子ID，作为主键
  post_title VARCHAR(255), -- 帖子标题
  post_content TEXT, -- 帖子内容
  post_date DATE, -- 发布日期
  post_like INT -- 点赞数
);

-- 创建comment表，存储评论信息
CREATE TABLE comment (
  comment_id VARCHAR(50) PRIMARY KEY, -- 评论ID，作为主键
  post_id VARCHAR(50), -- 帖子ID，作为外键
  comment_content TEXT, -- 评论内容
  comment_date DATE, -- 评论日期
  comment_like INT -- 点赞数
);
```

