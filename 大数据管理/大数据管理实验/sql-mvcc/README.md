## 可重复读事务隔离级别

为了支持MVCC（多版本并发控制），MySQL需要选用"可重复读"（REPEATABLE READ）事务隔离级别。

在"可重复读"事务隔离级别下，MySQL使用MVCC来处理并发事务。MVCC通过创建数据的快照视图（snapshot view）来实现事务的隔离性。每个事务在开始时会创建一个一致性的快照视图，该视图会记录事务开始时数据库中的数据状态。事务执行期间，其他事务对数据的修改不会对当前事务的查询结果产生影响。

"可重复读"事务隔离级别确保了每个事务在整个过程中看到的数据是一致的，即使其他事务对数据进行了修改。这种隔离级别适用于多用户并发访问数据库的场景，并保证了事务的ACID特性。

需要注意的是，MySQL默认的事务隔离级别是"可重复读"，但也可以通过设置来修改事务隔离级别。可以使用以下语句来设置事务隔离级别：
```sql
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
```

通过选择"可重复读"事务隔离级别，MySQL能够支持MVCC并发控制，保证了事务的一致性和隔离性。

## 读写并发

案例背景：假设有一个商品库存表（inventory），记录了每个商品的编号、名称和库存数量。我们将使用MySQL数据库的InnoDB存储引擎，并选用"可重复读"（REPEATABLE READ）事务隔离级别来支持MVCC。

1. 创建商品库存表（inventory）：
```sql
CREATE TABLE inventory (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    quantity INT
);
```

2. 插入初始数据：
```sql
INSERT INTO inventory (id, name, quantity)
VALUES (1, '商品A', 10), (2, '商品B', 5), (3, '商品C', 3);
```

3. 用户A和用户B同时读取商品A的库存数量：
```sql
-- 用户A执行的查询
SELECT quantity FROM inventory WHERE id = 1;

-- 用户B执行的查询
SELECT quantity FROM inventory WHERE id = 1;
```
结果：用户A和用户B都会得到相同的库存数量，例如结果为10。

原因：在"可重复读"事务隔离级别下，每个事务读取的是一个一致性的快照（snapshot）视图，即使其他事务对数据进行了修改。因此，用户A和用户B在同一时刻读取的是相同的库存数量。

4. 用户A开始一个事务，准备更新商品A的库存数量：
```sql
-- 用户A开始事务
START TRANSACTION;

-- 用户A执行更新操作
UPDATE inventory SET quantity = quantity - 1 WHERE id = 1;
```

5. 用户B在用户A事务未提交时，尝试读取商品A的库存数量：
```sql
-- 用户B执行的查询
SELECT quantity FROM inventory WHERE id = 1;
```
结果：用户B仍然会得到库存数量为10（未被修改前的值）。

原因：在"可重复读"事务隔离级别下，读取的是事务开始时的一致性快照视图。即使用户A已经修改了库存数量并且未提交事务，用户B仍然无法看到用户A的修改。

6. 用户A提交事务：
```sql
-- 用户A提交事务
COMMIT;
```

7. 用户B再次尝试读取商品A的库存数量：
```sql
-- 用户B执行的查询
SELECT quantity FROM inventory WHERE id = 1;
```
结果：用户B会得到库存数量为9（减少1后的值）。

原因：用户A提交事务后，用户B再次查询时会读取到最新的库存数量。MVCC会根据事务的提交时间和开始时间来决定用户B所看到的数据版本。

通过以上案例，我们展示了MySQL InnoDB存储引擎下的MVCC多版本并发控制特性。不同用户在同一时刻读取数据时，可以看到一致性的快照视图，并发更新操作不会相互干扰，保证了事务的ACID特性。

## 写写并发

先查询一次quantity

用户A

```mysql
START TRANSACTION;

UPDATE vendor set quantity=quantity-1 where id = 1;
```

用户B

```mysql
START TRANSACTION;

UPDATE vendor set quantity=quantity-1 where id = 1;
```

用户A commit

用户B commit

再查询一次quantity