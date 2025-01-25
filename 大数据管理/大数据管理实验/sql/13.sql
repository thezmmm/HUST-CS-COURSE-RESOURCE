SELECT
    JSON_UNQUOTE(JSON_EXTRACT(business_info, '$.name')) AS name,
    JSON_UNQUOTE(JSON_EXTRACT(business_info, '$.review_count')) AS review_count,
    IF(JSON_EXTRACT(business_info, '$.hours.Tuesday') IS NULL, 0, 1) AS is_open_on_tuesday,
	num,
    hours_in_a_week
FROM (
        SELECT
            business_id,business_info
        FROM
            business
        ORDER BY
            JSON_EXTRACT(business_info, '$.review_count') DESC
        LIMIT 3
    ) b1 left join(

	select business_id,
	ROW_NUMBER() OVER (PARTITION BY business_id ORDER BY hours_in_a_week) as num,
	hours_in_a_week
from(
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Monday') as hours_in_a_week
	from business
	union all
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Tuesday') as hours_in_a_week
	from business
	union all
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Wednesday') as hours_in_a_week
	from business
	union all
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Thursday') as hours_in_a_week
	from business
	union all
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Friday') as hours_in_a_week
	from business
	union all
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Saturday') as hours_in_a_week
	from business
	union all
	select business_id,
		JSON_EXTRACT(business_info, '$.hours.Sunday') as hours_in_a_week
	from business
) as h
where hours_in_a_week is not null
) b2 on b1.business_id = b2.business_id 
ORDER BY
	JSON_EXTRACT(business_info, '$.review_count') DESC,
    name ASC