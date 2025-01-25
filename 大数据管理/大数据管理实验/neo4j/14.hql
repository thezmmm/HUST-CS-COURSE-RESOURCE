MATCH (:UserNode)-[:Review]->(r:ReviewNode)
  -[:Reviewed]->(b:BusinessNode)
    -[:IN_CATEGORY]->(c:CategoryNode {category: 'Zoos'})
WHERE r.stars = '5.0'
RETURN DISTINCT b.city as city