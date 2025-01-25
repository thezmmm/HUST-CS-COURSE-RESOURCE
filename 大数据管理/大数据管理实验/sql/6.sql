-- 查询商户的原始 business_info
SELECT JSON_PRETTY(business_info) AS original_info
FROM business
WHERE business_id = '4r3Ck65DCG1T6gpWodPyrg';

-- 更新商户的 business_info
UPDATE business
SET business_info = JSON_SET(
                        JSON_SET(
                            JSON_SET(
                                JSON_SET(
                                    business_info,
                                    '$.hours.Tuesday',
                                    '16:0-23:0'
                                ),
                                '$.stars',
                                '4.5'
                            ),
                            '$.attributes.WiFi',
                            'Free'
                        ),
                        '$.modified_at',
                        CURRENT_TIMESTAMP
                    )
WHERE business_id = '4r3Ck65DCG1T6gpWodPyrg';

-- 查询商户的更新后的 business_info
SELECT JSON_PRETTY(business_info) AS updated_info
FROM business
WHERE business_id = '4r3Ck65DCG1T6gpWodPyrg';