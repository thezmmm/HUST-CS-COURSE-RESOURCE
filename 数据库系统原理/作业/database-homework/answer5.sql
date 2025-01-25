-- 5.6
select jname from j
where jno in (
	select jno from spj
	where sno = (
		select sno from s
        where city='上海'
    )
);

-- 5.7
select jno from j
where jno not in(
	select distinct jno from spj
	join s on s.sno=spj.sno
    where s.city='天津'
);

-- 5.8
update p
set color='蓝'
where color='红';

-- 5.9
update spj
set sno = 'S3'
where sno='S5' and jno='J4' and pno = 'P6';

-- 5.10
delete from s
where sno = 'S2';
delete from spj
where sno = 'S2';

-- 5.11
insert spj
values("S2","P4","J6",200);