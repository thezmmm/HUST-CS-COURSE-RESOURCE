SELECT
	JSON_KEYS(business_info) AS keys_info,
    JSON_LENGTH(business_info) AS key_num_info,
    JSON_KEYS(JSON_EXTRACT(business_info, '$.attributes')) AS keys_attr,
    JSON_LENGTH(JSON_EXTRACT(business_info, '$.attributes')) AS key_num_attr
FROM business
LIMIT 5;