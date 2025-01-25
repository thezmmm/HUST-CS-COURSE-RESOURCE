MATCH (user:UserNode)
WHERE toInteger(user.fans) > 200
RETURN user.name, user.fans
LIMIT 10