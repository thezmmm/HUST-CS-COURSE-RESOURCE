# neo4j
MATCH (r:ReviewNode {reviewid: 'TIYgnDzezfeEnVeu9jHeEw'})
  -[:Reviewed]->(b:BusinessNode)
RETURN b

# Mongo
var r = db.review.findOne({ review_id: "TIYgnDzezfeEnVeu9jHeEw" }).business_id;
db.business.findOne({ business_id: r});