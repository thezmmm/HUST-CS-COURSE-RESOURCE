## 1

**简述数据库堆文件的链表和页目录两种组织方式中，空闲空间分别是如何组织的？**

**链表组织方式**

在链表组织方式中，空闲空间由一个称为“空闲空间链表”的链表来组织。该链表由指向空闲块的指针组成，每个指针表示一个空闲块的起始位置。当需要插入新数据时，系统会从空闲空间链表中找到第一个足够大的空闲块，并将新数据插入其中。如果空闲块不够大，则需要将其分裂成两个较小的块，将其中一个块作为新数据的存储空间。当删除数据时，该数据所占用的空间将被添加到空闲空间链表中，以便后续的插入操作可以使用它。

**页目录组织方式**

在页目录组织方式中，空闲空间由一个称为“空闲空间列表”的页目录来组织。该页目录包含了所有空闲页的信息，每个空闲页都有一个条目。每个条目包含了空闲页的大小、起始地址和下一个空闲页的索引等信息。当需要插入新数据时，系统会查找空闲页目录，找到第一个足够大的空闲页，并在其中分配存储空间。当删除数据时，该数据所占用的空间将被标记为“空闲”，并更新页目录中的相关信息，以便后续的插入操作可以使用它。

## 2

 **简述面向元组型的页设计中槽页方案的基本思想，并简要说明槽页方案相对于数组式的元组存储方案的好处。**

面向元组型的页设计中，槽页方案是一种将元组存储在固定大小的页上的方法。其基本思想是，将每个页划分成一个个固定大小的槽(slot)，每个槽都可以存储一个元组(tuple)，而元组并不一定需要占满整个槽。

槽页方案相对于数组式的元组存储方案有以下好处：

1. 空间利用率高：槽页方案允许元组不必占满一个槽，因此可以更加灵活地利用空间。尤其是在元组长度较短的情况下，可以有效减少浪费的空间。
2. 插入和删除效率高：由于每个槽的大小是固定的，因此插入和删除元组时不需要进行大量的移动操作，只需修改指针即可，从而提高了效率。
3. 可以处理变长元组：槽页方案也可以很好地处理变长元组，只需将变长部分存储在另一块内存中，并在槽中保存指向该内存块的指针即可。

## 3

**设有学生关系S(SNO, SNAME, SDEPT)存储学生的学号、姓名和所属院系，学生选课关系SC(SNO, CNO, SCORE)存储学生选课记录的学号、课号和成绩，现有查询的SQL语句“SELECT S.SNO, CNO, SCORE FROM S, SC WHERE S.SNO=SC.SNO”，请画出查询计划的语法树，请写出该查询语法树的处理模型采用向量模型时每个查询算子的伪代码（设算子中每次处理的一个batch的大小为500）。**

        SELECT
           |
         PROJECT(S.SNO, CNO, SCORE)
           |
          JOIN
         /   \
        S     SC

#### 算子1: 扫描关系S

```python
batch_size = 500
pos = 0
while True:
    # 从磁盘读取batch_size条记录
    records = S[pos: pos + batch_size]
    if not records:
        break
    for record in records:
        # 输出学号
        output(record[SNO], None, None)
    pos += batch_size
```

#### 算子2: 扫描关系SC

```python
batch_size = 500
pos = 0
while True:
    # 从磁盘读取batch_size条记录
    records = SC[pos: pos + batch_size]
    if not records:
        break
    for record in records:
        # 输出学号、课程号和成绩
        output(record[SNO], record[CNO], record[SCORE])
    pos += batch_size
```

#### 算子3: 哈希连接算子

```python
batch_size = 500
# 构建哈希表
hash_table = {}
for record in SC:
    sno, cno, score = record[SNO], record[CNO], record[SCORE]
    hash_table.setdefault(sno, [])
    hash_table[sno].append((cno, score))

pos = 0
while True:
    # 从磁盘读取batch_size条记录
    records = S[pos: pos + batch_size]
    if not records:
        break
    for record in records:
        sno = record[SNO]
        # 从哈希表中查找选课记录
        if sno in hash_table:
            for cno, score in hash_table[sno]:
                # 输出学号、课程号和成绩
                output(sno, cno, score)
    pos += batch_size
```

## 4

**画出DBMS缓冲池的结构示意图，并结合缓冲池的内部结构说明一般情况下执行引擎访问数据页面过程。说明其中什么情况下执行引擎读数据页面会触发磁盘页面的写操作？**

<img src="C:\Users\MYH\Desktop\6B60FFAFF91604AD0FEF0ACAC8ADCDC6.jpg" alt="6B60FFAFF91604AD0FEF0ACAC8ADCDC6" style="zoom:25%;" />

DBMS缓冲池包含多个缓冲帧。每个缓冲帧都可以存储一个磁盘数据页。当需要读取或写入磁盘数据页时，DBMS会将其加载到缓冲池中的一个缓冲帧中，并将该缓冲帧标记为“已占用”。

为了跟踪哪些缓冲帧被哪些数据页占用，DBMS内部使用一个称为“页表”的数据结构。页表记录了每个缓冲帧当前包含的数据页的标识符和状态。

如果一个应用程序需要访问一个磁盘数据页，DBMS会首先查找该数据页是否已经位于缓冲池中的某个缓冲帧中。如果是，则DBMS直接返回该缓冲帧；否则，DBMS会将该数据页加载到一个空闲缓冲帧中，并更新页表来反映该缓冲帧现在占用的数据页。当缓冲帧不再需要时，DBMS会将其标记为空闲状态，并将相应的页表项清除。