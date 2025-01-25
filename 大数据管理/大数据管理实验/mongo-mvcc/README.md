## login

```shell
mongo 123.60.16.121:30000
mongo 60.204.134.47:30000

use testdb;
```

## 创建事务

```sql
const session1 = db.getMongo().startSession();
session1.startTransaction();
const collection1 = session1.getDatabase("test").getCollection("testmvcc");
```

```sql
const session2 = db.getMongo().startSession();
session2.startTransaction();
const collection2 = session2.getDatabase("test").getCollection("testmvcc");
```



## 读写并发

U1

```sql
collection1.find()
```

U2

```sql
collection2.insert({Key:"val"});
```

U1

```sql
collection1.find()
```

U2

```sql
session2.commitTransaction();
```

U1

```sql
collection1.find()
```

