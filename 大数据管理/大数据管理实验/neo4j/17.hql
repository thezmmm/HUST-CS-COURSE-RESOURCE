MATCH (u1:UserNode {userid: 'tvZKPah2u9G9dFBg5GT0eg'})
-[:Review]->(:ReviewNode)-[:Reviewed]->(b1:BusinessNode)
WITH u1, COLLECT(DISTINCT b1) AS u1_businesses
MATCH (u2:UserNode)-[:Review]->(:ReviewNode)-[:Reviewed]->(b2:BusinessNode)
WHERE u2 <> u1 AND b2 IN u1_businesses
WITH u1, u2, COLLECT(DISTINCT b2) AS common_businesses
RETURN u1.name, u2.name, SIZE(common_businesses) AS common_business_count
ORDER BY common_business_count DESC
