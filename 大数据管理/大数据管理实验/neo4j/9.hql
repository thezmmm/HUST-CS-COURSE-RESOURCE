MATCH (:BusinessNode {businessid: 'tyjquHslrAuF5EUejbPfrw'})
  -[:IN_CATEGORY]->(c:CategoryNode)
RETURN COLLECT(c.category)