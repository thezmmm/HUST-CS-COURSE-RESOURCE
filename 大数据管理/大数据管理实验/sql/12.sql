SELECT u.user_id,b.business_id, JSON_MERGE_PATCH(b.business_info, u.user_info) AS merged_info
FROM (
    SELECT t.business_id
    FROM (
        SELECT business_id, COUNT(*) AS tip_count
        FROM tip
        GROUP BY business_id
        ORDER BY tip_count DESC
        LIMIT 1
    ) AS t
) AS bt
JOIN business b ON bt.business_id = b.business_id
JOIN (
    SELECT t.user_id
    FROM (
        SELECT user_id, COUNT(*) AS tip_count
        FROM tip
        GROUP BY user_id
        ORDER BY tip_count DESC
        LIMIT 1
    ) AS t
) AS ut
JOIN user u ON ut.user_id = u.user_id;