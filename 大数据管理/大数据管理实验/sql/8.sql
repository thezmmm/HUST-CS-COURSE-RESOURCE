SELECT 
    state,
    JSON_OBJECTAGG(city, city_count) AS city_counts
FROM (
    SELECT 
        business_info->>'$.state' AS state,
        business_info->>'$.city' AS city,
        COUNT(*) AS city_count
    FROM 
        business
    GROUP BY 
        state, city
) AS subquery
GROUP BY 
    state
ORDER BY 
    state ASC;