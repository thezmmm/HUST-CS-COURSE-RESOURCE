SELECT
	JSON_EXTRACT(b1.business_info, '$.name') as name1,
    JSON_EXTRACT(b1.business_info, '$.city') as city1,
    JSON_EXTRACT(b2.business_info, '$.name') as name2,
    JSON_EXTRACT(b2.business_info, '$.city') as city2,
    JSON_EXTRACT(b1.business_info, '$.hours') as hours1,
    JSON_EXTRACT(b2.business_info, '$.hours') as hours2,
    CASE WHEN JSON_OVERLAPS(b1.business_info -> '$.hours', b2.business_info -> '$.hours') THEN 1 ELSE 0 END AS is_overlap
FROM
    business AS b1
    JOIN business AS b2 ON b1.business_id <> b2.business_id
WHERE
    JSON_EXTRACT(b1.business_info, '$.city') = 'EdMonton'
    AND JSON_EXTRACT(b2.business_info, '$.city') = 'Elsmere';