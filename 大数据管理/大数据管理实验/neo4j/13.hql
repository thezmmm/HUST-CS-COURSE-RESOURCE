MATCH (business:BusinessNode)
WHERE toInteger(business.reviewcount) > 5000
WITH COUNT(DISTINCT business) AS cnt
MATCH (business:BusinessNode)
WHERE toInteger(business.reviewcount) > 5000
WITH business, COUNT(*) AS count, cnt
WITH business.name AS name, count, count*1.0/cnt AS popularity, business.reviewcount AS reviewcount
RETURN popularity, name, reviewcount
ORDER BY reviewcount DESC