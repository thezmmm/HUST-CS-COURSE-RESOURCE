SELECT t.user_id, u.user_info->>'$.name' AS user_name, GROUP_CONCAT(t.tip_info->>'$.text' ORDER BY t.tip_info->>'$.date') AS tips
FROM user u
JOIN (
    SELECT user_id
    FROM user
    WHERE user_id = '__1cb6cwl3uAbMTK3xaGbg'
) f ON REGEXP_LIKE(u.user_info->>'$.friends', CONCAT('(^|, )', f.user_id, '(,|$)'))
JOIN tip t ON u.user_id = t.user_id
GROUP BY t.user_id, u.user_info->>'$.name'
ORDER BY user_name ASC;

-- "MAPcsh_0tHDpRw3dqEI1jg, TXnuPEDSNwIPSSndL2uiKw, N-qPxrzdRaO9xG5VMjn8pA, IaqwLtG5Se-kt_MHBOalag, s1t-N7hhU-6ThJeQPVuOJQ"