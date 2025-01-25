## 1

```
MATCH (user:UserNode)-[:Review]->(review:ReviewNode)-[:Reviewed]->(business:BusinessNode)
WITH user,count(distinct(business)) AS reviewCount
WHERE reviewCount > 5
RETURN user.name,user.funny,user.fans
```





## 2

```
 mongoimport --db Mydb --collection collection41 --file ~/result/task4/records2.json --jsonArray
```

```
db.NewBusiness.aggregate([{$group: {_id: "$user.name",count: { $sum: 1 }}}, { $sort: { count: -1 }} ])
```



## 3

```
MATCH p=(n:BusinessNode)-[r:IN_CATEGORY]->(x:CategoryNode) 
RETURN n.name,n.city,x.category
```

```
mongoimport -d yelp -c Name --type csv --headerline --file ./allbusiness.csv
```

