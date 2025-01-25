db.user.find({name:"Wanda").explain()

### 1

#### 题目
查询review集合的2条数据，跳过前6条

#### 解析

```js
db.review.find().skip(6).limit(2)
```

### 2

#### 题目
查询business集合中city是Goodyear的5条数据。

#### 解析

```js
db.business.find({ city: "Las Vegas" }).limit(5)
```

### 3

#### 题目

查询user集合中name是Steve的user，只需要返回useful和cool,限制10条数据。

#### 解析

```js
db.user.find({ name: "Steve" }, { _id: 0, useful: 1, cool: 1 }).limit(10)
```

### 4

#### 题目
查询user集合中funny位于[66，67，68]的user，只需返回name和funny，限制20条数据。

#### 解析

```js
db.user.find({ funny: { $in: [66, 67, 68] } }, { _id: 0, name: 1, funny: 1 }).limit(20)
```

### 5

#### 题目
查询user集合中15≤cool<20且useful≥50的user，限制10条。

#### 解析

```js
db.user.find({ cool: { $gte: 15, $lt: 20 }, useful: { $gte: 50 } }).limit(10)
```

### 6

#### 题目
统计business一共有多少条数据，并使用explain查询执行计划，了解MongoDB对集函数的执行方式。

#### 解析
先统计，再用`.explain("executionStats")`查询MongoDB对`count()`命令的执行计划

```js
db.business.count()
> 192609
db.business.explain("executionStats").count()
```

### 7

#### 题目
查询business集合city为Westlake或者Charlotte的数据。

#### 解析

使用`$or`操作符

```js
db.business.find({$or: [{city: "Westlake"}, {city: "Calgary"}]})
```

### 8

#### 题目
查询business集合中，categories为6种的商户信息，显示这6种类别，限制10条

#### 解析

```js
db.business.find({categories: {$size: 6}}, {_id: 0, name: 1, categories: 1}).limit(10)
```

### 9

#### 题目
使用`explain`看`db.business.find({business_id: "5JucpCfHZltJh5r1JabjDg"})`的执行计划，了解该查询的执行计划及查询执行时间，并给出物理优化手段，以提高查询性能，通过优化前后的性能对比展现优化程度。

#### 解析

```js
db.business.find({business_id: "5JucpCfHZltJh5r1JabjDg"}).explain("executionStats")
```

### 10

#### 题目
统计各个星级的商店的个数，返回星级数和商家总数，按照星级降序排列。

#### 解析

```js
db.business.aggregate([{$group:{_id:"$stars", count:{$sum:1}}}, {$sort:{_id:-1}}])
```

### 11

#### 题目
创建一个review的子集合Subreview(取review的前五十万条数据)，分别对评论的内容建立全文索引，对useful建立升序索引，然后查询评价的内容中包含关键词delicious且useful大于9的评价。插入数据过程耗时约150s，建索引耗时约60s。

#### 解析
首先使用 `$limit` 管道操作符将 review 集合中的文档限制为前 500,000 条，然后使用 `$out` 管道操作符将结果输出到一个名为Subreview的新集合中，这样就创建一个新的子集合 Subreview。

```js
db.review.aggregate([{$limit: 500000}, {$out: "Subreview"}])
```
创建前后都可以使用`show collections`来查看目前数据库中的集合，可以看到执行以上语句后数据库中多了一条叫做Subreview的集合，且我们查询其文档数目，为50w。

```js
db.Subreview.find().limit(1)
```

对评论的内容建立全文索引，对useful建立升序索引
```js
// 对评论的内容建立全文索引
db.Subreview.createIndex({text: "text"})

// MongoDB默认为字段"useful"创建了升序索引,降序索引通过指定-1来实现。
db.Subreview.createIndex({useful: 1})
```

查询
```js
db.Subreview.find({$text: {$search: "delicious"}, useful: {$gt: 9}})
```

### 12

#### 题目
在Subreview集合中统计评价中useful、funny和cool都大于6的商家，返回商家id及平均打星，并按商家id降序排列

#### 解析

```js
db.Subreview.aggregate([
  {$match: {useful: {$gt: 6}, funny: {$gt: 6}, cool: {$gt: 6}}},
  {$group: {_id: "$business_id", average_stars: {$avg: "$stars"}}},
  {$sort: {_id: -1}}
])
```

### 13

#### 题目
查询距离商家 `xvX2CttrVhyG2z1dFg_0xw(business_ id)` 100米以内的商家，只需要返回商家名字，地址和星级。*提示：使用2dsphere建立索引、获取商家地理坐标、使用坐标进行查询*

```js
db.business.find({business_id: "xvX2CttrVhyG2z1dFg_0xw"})
```

```js
db.business.createIndex({ loc: "2dsphere" })
```

```js
db.business.find({
  loc: {
    $near: {
      $geometry: {
        type: "Point",
        coordinates: [-112.3955963552, 33.4556129678]
      },
      $maxDistance: 100
    }
  }
}, {
  _id: 0,
  name: 1,
  address: 1,
  stars: 1
})
```

### 14

#### 题目
在集合Subreview上建立索引，统计出用户从2017年开始发出的评价有多少，按照评价次数降序排序，需要返回用户id和评价总次数，只显示前20条结果。

#### 解析

```js
db.Subreview.createIndex({user_id: 1, date: 1})
```

```js
db.Subreview.aggregate([
  {
    $match: {
      $expr: {
        $gte: [
          { $toDate: "$date" },
          ISODate("2017-01-01T00:00:00Z")
        ]
      }
    }
  },
  {
    $group: {
      _id: "$user_id",
      count: { $sum: 1 }
    }
  },
  {
    $sort: {
      count: -1
    }
  },
  {
    $limit: 20
  },
  {
    $project: {
      _id: 1,
      count: 1
    }
  }
])
```

### 15

#### 题目
使用mapreduce计算每个商家的评价的平均分（建议在Subreview集合上做，review过于大）,不要直接使用聚合函数。

#### 解析

1. 定义 Map 函数：在 Map 函数中，将每个商家的评价分数作为键（key），并将分数值和计数器作为值（value）发射出去。

```js
var mapFunction = function() {
  emit(this.business_id, { score: this.stars, count: 1 });
};
```

2. 定义 Reduce 函数：在 Reduce 函数中，对每个商家的评价分数进行累加求和，并计算总评价数。

```js
var reduceFunction = function(key, values) {
  var reducedValue = { score: 0, count: 0 };
  
  values.forEach(function(value) {
    reducedValue.score += value.score;
    reducedValue.count += value.count;
  });
  
  return reducedValue;
};
```

3. 执行 MapReduce 操作：

```js
db.Subreview.mapReduce(
  mapFunction,
  reduceFunction,
  {
    out: { inline: 1 }, // 将结果以内联方式输出
    finalize: function(key, reducedValue) {
      reducedValue.average = reducedValue.score / reducedValue.count; // 计算平均分
      return reducedValue;
    }
  }
)
```

上述代码将执行 MapReduce 操作，并将结果以内联方式输出。在输出结果的 `finalize` 阶段，将计算每个商家的评价平均分，并将其添加到输出结果中。
