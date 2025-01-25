MATCH(:UserNode{name:'Allison'})-[:HasFriend]->(friend)
WITH friend.name as friendsList, size((friend)-[:HasFriend]-()) as number0fFoFs
RETURN friendsList,number0fFoFs