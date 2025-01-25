MATCH (b:BusinessNode)-[IN_CATEGORY]->(:CategoryNode {category: 'Salad'}) 
WITH b.city AS cityName, COUNT(*) AS numOfBusiness 
RETURN cityName, numOfBusiness 
ORDER BY numOfBusiness DESC
LIMIT 5