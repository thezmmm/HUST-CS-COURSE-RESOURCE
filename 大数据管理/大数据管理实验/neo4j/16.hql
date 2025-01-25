MATCH (user:UserNode)
WHERE toInteger(user.fans) > 300
SET user.flag = user.fans

MATCH (user:UserNode)
WHERE toInteger(user.flag) >8000
RETURN user

MATCH (user:UserNode)
WHERE toInteger(user.flag) >= 456 AND toInteger(user.flag) <= 3456
SET user.flag = 8001

MATCH (user:UserNode)
WHERE user.flag > 8000
REMOVE user.flag



CREATE INDEX FOR (user:UserNode) ON (user.flag)

// 备注，查找索引名字并删除索引的方法
CALL db.indexes()
DROP INDEX `name with no quote`