use carrot_hole;

-- 创建user表，存储用户信息
create table user
(
    user_id       varchar(50) not null
        primary key,
    user_name     varchar(50) null,
    password      varchar(50) null,
    level         int         null,
    register_date date        null,
    login_date    date        null
);

-- 创建post表，存储帖子信息
create table post
(
    post_id      varchar(50)  not null
        primary key,
    post_title   varchar(255) null,
    post_content text         null,
    post_date    date         null,
    post_like    int          null,
    user_id      varchar(50)  not null
);
 

-- 创建comment表，存储评论信息
create table comment
(
    comment_id      varchar(50) not null
        primary key,
    post_id         varchar(50) null,
    comment_content text        null,
    comment_date    date        null,
    comment_like    int         null,
    user_id         varchar(50) not null
);