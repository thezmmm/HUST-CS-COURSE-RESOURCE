-- 4.1
select sno
from spj
where JNO = 'J1';

-- 4.2
select sno
from spj
where jno='J1' and pno='P1';


-- 4.3
select sno
from spj,p
where spj.pno=p.pno and p.color='红' and jno='J1';

-- 4.4
select distinct jno
from spj
where jno not in
    (select jno
    from spj,s,p
    where  s.sno=spj.sno 
    and p.pno=spj.pno
    and city='天津'  
    and color='红'); 
    
-- 4.5
select distinct jno
from spj spj1
where not exists
    (select *
    from spj spj2
    where spj2.sno='S1'
          and not exists
          (select *
          from spj spj3
          where jno = spj1.jno
             and pno = spj2.pno)
	);
