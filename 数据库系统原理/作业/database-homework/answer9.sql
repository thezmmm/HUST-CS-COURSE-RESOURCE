create view san_jian
as
  select sno,pno,qty
  from spj,j
  where spj.jno=j.jno and jname='三建';
  
-- 9.1
select pno,qty
from san_jian;

-- 9.2
select *
from san_jian
where sno='S1';