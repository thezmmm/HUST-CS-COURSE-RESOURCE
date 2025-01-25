SELECT * 
FROM business 
WHERE JSON_EXTRACT(business_info , '$.city') = 'Tampa' 
ORDER BY JSON_EXTRACT(business_info, '$.review_count') DESC 
LIMIT 10;