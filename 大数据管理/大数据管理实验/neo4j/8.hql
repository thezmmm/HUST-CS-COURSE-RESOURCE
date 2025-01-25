MATCH (:BusinessNode {businessid: 'tyjquHslrAuF5EUejbPfrw'})
  -[:IN_CATEGORY]->(c:CategoryNode)
RETURN COUNT(DISTINCT c)

PROFILE MATCH (:BusinessNode {businessid: 'tyjquHslrAuF5EUejbPfrw'})
  -[:IN_CATEGORY]->(c:CategoryNode)
RETURN COUNT(DISTINCT c)