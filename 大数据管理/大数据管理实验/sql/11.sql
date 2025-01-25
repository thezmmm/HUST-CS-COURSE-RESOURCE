-- EXPLAIN
SELECT
    user_info->>'$.name' AS user_name,
    user_info->>'$.average_stars' AS average_stars,
    JSON_ARRAY(
        SUM(user_info->>'$.funny'),
        SUM(user_info->>'$.useful'),
        SUM(user_info->>'$.cool'),
        SUM(user_info->>'$.funny')+SUM(user_info->>'$.useful')+SUM(user_info->>'$.cool')
    ) AS funny_useful_cool_sum
FROM
    user
WHERE
    user_info->>'$.funny' > 2000
    AND user_info->>'$.average_stars' > 4.0
GROUP BY
    user_name, average_stars
ORDER BY
    average_stars DESC
LIMIT 10; 