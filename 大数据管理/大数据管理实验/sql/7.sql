-- 插入新商户记录
INSERT INTO business (id, business_info)
SELECT 'aaaaaabbbbbbcccccc2023', business_info
FROM business
WHERE business_id = '5d-fkQteaqO6CSCqS5q4rw';

-- 删除新商户记录的name键值对
UPDATE business
SET business_info = JSON_REMOVE(business_info, '$.name')
WHERE business_id = 'aaaaaabbbbbbcccccc2023';

-- 查询新商户记录的所有信息
SELECT *
FROM business
WHERE business_id = 'aaaaaabbbbbbcccccc2023';