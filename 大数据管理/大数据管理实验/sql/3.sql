SELECT 
    business_info -> '$.name' AS name,
    JSON_TYPE(business_info -> '$.name') AS name_type,
    business_info -> '$.stars' AS stars,
    JSON_TYPE(business_info -> '$.stars') AS stars_type,
    business_info -> '$.attributes' AS attributes,
    JSON_TYPE(business_info -> '$.attributes') AS attributes_type
FROM
    business
LIMIT 5;