SELECT 
    business_info -> '$.name' AS name,
    business_info -> '$.attributes' AS attributes,
    business_info -> '$.hours' AS hours
FROM
    business
WHERE
    business_info -> '$.attributes.HasTV' = 'True'
    AND (business_info -> '$.hours.Sunday' IS NULL OR business_info -> '$.hours' IS NULL)
ORDER BY
    name ASC
LIMIT 10;