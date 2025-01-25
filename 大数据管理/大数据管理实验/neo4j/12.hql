MATCH (b:BusinessNode)
WITH b.name AS name, COUNT(*) AS count
WHERE count > 1
RETURN name, count
ORDER BY count DESC
LIMIT 10