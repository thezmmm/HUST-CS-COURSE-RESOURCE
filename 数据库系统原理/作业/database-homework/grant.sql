-- 1
grant all privileges 
on table 学生,班级 
to U1 
with grant option;

-- 2
grant select,update(家庭住址) on table 学生 to U2;

-- 3
grant select on table 学生 to public;

-- 4
grant select,update on table 学生 to R1;

-- 5
grant R1 to U1 with grant option;

-- 7.3
grant select
on table 职工
where user()=姓名 to all

-- 7.5
grant alter
on table 职工,部门
to 张新;

-- 7.6
grant all privileges
on table 职工,部门
to 周平
with grant option

-- 7.7
create view viewname(max,min,mean)
as select max(工资),min(工资),avg(工资) from 职工
group by 部门号

grant select on view viewname to 杨兰;
