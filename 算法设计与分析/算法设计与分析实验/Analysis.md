---
ID:1563081082
Name:Thezmmm
---

[源码地址(JAVA)](https://github.com/thezmmm/HUST-POJ-Practice)

```java
import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        if(scan.hasNext()){
            String s = scan.next();
        }
        scan.close();
    }
}
```

## POJ1000

```java
import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String a = scan.next();
        String b = scan.next();
        System.out.println(Integer.parseInt(a) + Integer.parseInt(b));
        scan.close();
    }
}
```

## POJ1005

### 题目分析

题目给出了若干坐标点，半圆以每次增大50大小的面积来增加，所求为多少次增大后，可以覆盖到给出的坐标点

拥有的数据为，坐标点的横纵坐标，以及半圆每次增大的面积大小，想要提高运行速度，显然要根据以上数据，一次计算出半圆增大次数，不难想到可以先根据坐标算出坐标点到圆心距离，然后算出覆盖到该点所需的面积，除以半圆每次增大的大小即可。

### 算法设计

```java
import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        for(int i = 0;i < n;i++){
            float x = scan.nextFloat();
            float y = scan.nextFloat();
            double d = Math.sqrt(x*x+y*y);
            double s = Math.PI*d*d/2;
            int year = (int) Math.ceil(s/50);
            System.out.println("Property "+(i+1)+": This property will begin eroding in year "+year+".");
        }
        System.out.println("END OF OUTPUT.");
    }
}
```

1. 读取每组坐标点的数据
2. 计算出覆盖到该坐标点所需的面积大小
3. 用(2)中计算出的面积大小除以半圆每次增大的大小

### 性能分析

- 时间复杂度O(n)

  需要对所有坐标点进行遍历，n为坐标点的数量

- 空间复杂度O(1)

  开辟的空间大小与输入的坐标数量无关，只用到了常数级的空间

### 运行测试

## *POJ1753

### 题目分析

题目给出了一个**固定大小**的4*4棋盘，又由于对同一个点位进行偶数次翻转相当于不进行翻转，因此对每个点位仅存在两种情况：翻转/不翻转。共有2<sup>16</sup>种情况，即256种情况，因此是可以进行暴力枚举的。

### 算法设计

```java
import java.util.Scanner;

/**
 * @author MYH
 * @time 2022-11-16
 */
public class Main {
    public static int[][] direction = new int[][]{{1,0},{-1,0},{0,1},{0,-1},{0,0}};
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int[][] board = new int[4][4];
//        read data: w->0 b->1
        for(int i = 0;i < 4;i++){
            String c = scan.next();
            for(int j = 0;j < 4;j++){
                if(c.charAt(j) == 'w'){
                    board[i][j] = 0;
                }else{
                    board[i][j] = 1;
                }
            }
        }
//        function test
//        test function flip
//        int[][] newBoard = flip(board,1);
//        for(int i = 0;i < 4;i++){
//            System.out.println(Arrays.toString(newBoard[i]));
//        }
//        test isFinished
//        System.out.println(isFinished(flip(board,0)));
        int ans = dfs(board,0,0);
        System.out.println(ans==17?"Impossible":ans);
    }

    private static int dfs(int[][] board,int cur,int count){
        if(isFinished(board)){
            return count;
        }
        if(cur >= 16){
            return 17;
        }
        // don't flip current node
        int t1 = dfs(board,cur+1,count);
        // flip current node
        flip(board,cur);
        int t2 = dfs(board,cur+1,count+1);
        flip(board,cur);
//        return min flip count
        return Math.min(t1,t2);
    }

//  flip cur node
    private static void flip(int[][] board,int cur){
        // calculate current x and y
        int x = cur/4;
        int y = cur-x*4;
        for(int[] dir:direction){
            // make sure x and y in the range
            if(x+dir[0] >=0 && x+dir[0] < 4 && y+dir[1]>=0 && y+dir[1] < 4){
                board[x+dir[0]][y+dir[1]] ^= 1;
            }
        }
    }
//    judge if there is different number
    private static boolean isFinished(int[][] board){
        int x = board[0][0];
        for(int i = 0;i < 4;i++){
            for(int j = 0;j < 4;j++){
                if(board[i][j] != x) {
                    return false;
                }
            }
        }
        return true;
    }
}
```

- isFinished

  判断函数，比较棋盘上的每个元素是否与第一个元素相同，从而判断是否达到目标

- flip

  翻转函数，负责完成一次翻转操作，遍历五个方向(上下左右以及本身)，对每个方向进行翻转，为了简化代码，读入的数据采用0和1存储，由于0^1=1,1^1=0，所以可以利用按位异或的性质来对每一位进行翻转，从而不必写额外的if判断语句

- dfs

  枚举过程使用递归的形式完成，分别需要考虑对一个点翻转和不翻转的情况，并取两种情况可能得到的最小值

  遍历点时仅使用一个数据cur来完成，通过x=cur/4,y=cur-x*4，来计算出cur表示的位置

  结束条件有两种

  - 达成目标，isFinished判断棋盘已经翻转完成
  - 已经遍历完了每一个点

### 性能分析

- 时间复杂度
- 空间复杂度

### 运行测试

## POJ3295

### 题目分析

此题中仅给出了5个逻辑变量，每个变量有 True 和 False 两种情况，枚举共有32种情况，数量较小，因此可以对全部情况进行枚举

### 算法设计

```java
import java.util.*;

/**
 * @author MYH
 * @time 2022-11-16
 */
public class P3295 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String s = scan.next();
        while(!s.equals("0")){
            if(help(s)){
                System.out.println("tautology");
            }else{
                System.out.println("not");
            }
            s = scan.next();
        }
    }

    // Enumerate each case
    private static boolean help(String str){
        Map<Character,Character> map = new HashMap<Character,Character>();
        char[] b = new char[]{'0','1'};
        for(char p:b){
            map.put('p',p);
            for(char q:b){
                map.put('q',q);
                for(char r:b){
                    map.put('r',r);
                    for(char s:b){
                        map.put('s',s);
                        for(char t:b){
                            map.put('t',t);
                            if(!judge(str,map)){
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    // judge if the str is true
    private static boolean judge(String str,Map<Character,Character> map) {
        for(Map.Entry<Character,Character> entry :map.entrySet()){
            str = str.replace(entry.getKey(), entry.getValue());
        }
        while(str.length() != 1){
            if(str.indexOf("K") != -1) {
                str = str.replace("K11", "1");
                str = str.replace("K10", "0");
                str = str.replace("K01", "0");
                str = str.replace("K00", "0");
            }
            if(str.indexOf("A") != -1) {
                str = str.replace("A11", "1");
                str = str.replace("A10", "1");
                str = str.replace("A01", "1");
                str = str.replace("A00", "0");
            }
            if(str.indexOf("C") != -1) {
                str = str.replace("C11", "1");
                str = str.replace("C10", "0");
                str = str.replace("C01", "1");
                str = str.replace("C00", "1");
            }
            if(str.indexOf("E") != -1) {
                str = str.replace("E11", "1");
                str = str.replace("E10", "0");
                str = str.replace("E01", "0");
                str = str.replace("E00", "1");
            }
            if(str.indexOf("N") != -1){
                str = str.replace("N1","0");
                str = str.replace("N0","1");
            }
        }
        return str.equals("1");
    }
}
```

1. 整体思路

   算法整体思路为，遍历五个逻辑变量为0或1的所有情况，对每种情况进行判断是否为真，当出现假时停止，说明该式不是永真式，直到遍历完全部情况，说明该式为永真式

2. 判断思路

   判断逻辑表达式的常规思路是使用栈来进行内容读取，但是此题的逻辑表达式对于每个逻辑操作符，没有很好的可以用来判断结束的标志，例如括号的右括号，因此这里枚举题干表中给出的所有情况，使用replace方法将式子进行不断化简，直到最简，即‘0’或‘1’为止

### 性能分析

- 时间复杂度O(nm<sup>2</sup>)

  其中，n为输入逻辑表达式的数量，m为逻辑表达式的长度

  对于每一组逻辑表达式，遍历逻辑变量的所有情况共需2的5次方，即32次

  对于每一次判断，需要将长为m的字符串化简至长度为1为止，每次replace可以将三个字符化为一个字符，因此```1+2t=m```，replace的时间复杂度为O(m)，所以总的时间复杂度为O(m<sup>2</sup>)

- 空间复杂度O(1)

  计算过程仅开辟常数级空间，因此空间复杂度为O(1)

### 运行测试

## POJ2366

### 题目分析

### 算法设计

```java
import java.util.*;

/**
 * @author MYH
 * @time 2022-11-17
 */
public class P2366 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        Set<Integer> set = new HashSet<>();
        int len1 = scan.nextInt();
        for(int i = 0;i < len1;i++){
            set.add(10000-scan.nextInt());
        }
        boolean flag = false;
        int len2 = scan.nextInt();
        for(int i = 0;i < len2;i++){
            if(set.contains(scan.nextInt())){
                flag = true;
            }
        }
        if(flag){
            System.out.println("YES");
        }else{
            System.out.println("NO");
        }
    }
}
```

### 性能分析

- 时间复杂度
- 空间复杂度

### 运行测试

## POJ2503

### 题目分析

### 算法设计

```java
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-17
 */
public class P2503 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        Map<String,String> map = new HashMap<String, String>();
        String read = scan.nextLine();
        while(!read.equals("")){
            String[] word = read.split(" ");
            map.put(word[1],word[0]);
            read = scan.nextLine();
        }
        while(scan.hasNext()){
            String key = scan.next();
            if(map.containsKey(key)) {
                System.out.println(map.get(key));
            }else{
                System.out.println("eh");
            }
        }

    }
}
```



### 性能分析

- 时间复杂度
- 空间复杂度

### 运行测试



## POJ3714

### 题目分析

此题显然为 求平面最近点对 的变形，考虑时需要将点对分为两组，必须在不同组之间求最小距离

### 算法设计

### 性能分析

- 时间复杂度
- 空间复杂度

### 运行测试

## POJ3233

### 题目分析

此题主要考察矩阵的运算，包括矩阵加，矩阵乘，矩阵幂，求解矩阵的幂次和，不难想到求高次幂需要大量时间，可以用低次幂来合成高次幂，从而避免对高次幂的多次计算

### 算法设计

```java
import java.io.BufferedInputStream;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-23
 */
public class P3233 {
    static Scanner in = new Scanner(new BufferedInputStream(System.in));
    static long mod;

    static class Mat {
        public long a[][];
        public int x;

        public Mat(int x) {
            a = new long[x][x];
            this.x = x;
        }

        public Mat mu(Mat t) {
            Mat ans = new Mat(x);
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < x; j++) {
                    for (int k = 0; k < x; k++) {
                        ans.a[i][j] += a[i][k] * t.a[k][j];
                    }
                    ans.a[i][j] %= mod;
                }
            }
            return ans;
        }

        public Mat add(Mat t) {
            Mat ans = new Mat(x);
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < x; j++) {
                    ans.a[i][j] = (a[i][j] + t.a[i][j]) % mod;
                }
            }
            return ans;
        }

        public Mat() {
            super();
        }

    }

    static Mat E;

    static void setE(int s) {
        E = new Mat(s);
        for (int i = 0; i < s; i++)
            E.a[i][i] = 1;
    }

    static Mat Z;

    static void setZ(int s) {
        Z = new Mat(s);
    }

    static Mat A;

    static void setA(int s) {
        A = new Mat(s);
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                A.a[i][j] = in.nextLong() % mod;
            }
        }
    }

    static class M {
        public Mat a[][];

        public M() {
            a = new Mat[2][2];
        }

        public void set(Mat t, Mat b, Mat c, Mat d) {
            a[0][0] = t;
            a[0][1] = b;
            a[1][0] = c;
            a[1][1] = d;
        }

        public M mu(M t) {
            M ans = new M();
            ans.a[0][0] = E;
            ans.a[1][0] = Z;
            ans.a[0][1] = t.a[0][1].add(a[0][1].mu(t.a[1][1]));
            ans.a[1][1] = a[1][1].mu(t.a[1][1]);
            return ans;
        }
    }

    static M x;
    static M e;

    static M pow(int t) {
        M ans = e;
        while (t > 0) {
            if ((t & 1) == 1) {
                ans = ans.mu(x);
            }
            x = x.mu(x);
            t >>= 1;
        }
        return ans;
    }

    static Mat ans;

    public static void main(String[] args) {
        x=new M();
        e=new M();
        while(in.hasNext()) {
            int n=in.nextInt(),k=in.nextInt();
            mod=in.nextLong();
            setE(n);setZ(n);setA(n);
            x.set(E, A, Z, A);
            e.set(E, Z, Z, E);
            ans=pow(k).a[0][1];
            for(int i=0;i<n;i++) {
                for(int j=0;j<n;j++) {
                    if(j!=0)System.out.print(" ");
                    System.out.print(ans.a[i][j]);
                }
                System.out.println();
            }
        }
    }
}
```

求解矩阵的幂次和，为减少计算次数，对和进行二分，根据k的奇偶进行分情况讨论即可
$$
S = A^1 + A^2 +...+A^{\frac{k-1}{2}}+A^{\frac{k-1}{2}}( A^1 + A^2 +...+A^{\frac{k-1}{2}})+A^k \quad k为奇数
$$

$$
S = A^1 + A^2 +...+A^{\frac{k}{2}}+A^{\frac{k}{2}}( A^1 + A^2 +...+A^{\frac{k}{2}}) \quad k为偶数
$$

### 性能分析

- 时间复杂度
- 空间复杂度

### 运行测试

## POJ2506

### 题目分析

此题对答案的求解为递推找规律，输入的参数只有一个，长方形的长度n，填充的方块的长度只有1和2，从长度为n-2填充到长度n时(1)，有三种方式；从长度为n-1填充到长度为n时(2)，有一种方式，其中(2)包含了(1)中的一种情况，因此递推式最终为
$$
f(n) = f(n-1) + 2*f(n-2)
$$
同时观察到样例给出的数据，无法用常规的整形数据类型存储，因此要用到高精度，因为此处乘数之一为常数，因此仅使用高精度加法即可，不必使用高精度乘法。

### 算法设计

```java
import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class P2506 {
    static Map<Integer,BigInteger> map = new HashMap<>();
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        map.put(0,new BigInteger("1"));
        map.put(1, new BigInteger("1"));
        map.put(2, new BigInteger("3"));
        while(scan.hasNext()){
            int n = scan.nextInt();
            System.out.println(ans(n));
        }
    }
    private static BigInteger ans(int n){
        if(map.containsKey(n)){
            return map.get(n);
        }
        BigInteger bi = ans(n-1).add(ans(n-2).add(ans(n-2)));
        map.put(n,bi);
        return map.get(n);
    }
}
```

使用哈希表对数据存储，避免重复计算，当访问到已经计算出的值时直接返回答案，并且每次保存当前计算的所有未保存值，从而降低计算次数与时间

### 性能分析

- 时间复杂度
- 空间复杂度

## *POJ1201

### 题目分析

题目意为有n个区间[ai,bi]，每个区间至少需要选ci个数.求出新的集合Z在满足所有约束条件下，至少包含多少个数。
用Si 表示0 - i 中被选出的数的个数.
约束条件：

1. Si >= Si - 1 ，从1 到 i 中选的数必定不会比从1 到 i -1中选的数少。

2. Si - Si-1 <= 1 **=>>** Si-1 >= Si - 1, 相邻之间选的数的个数差不会超过1个数。

3. Sb - Sa-1 >= c **=>>** Sb >= Sa-1 + c, [a,b] 中至少选c个数。

4. 从源点出发，一点可以走到所有边

注意到 Sb >= Sa-1 + c 这个条件，与单源最短路中的三角形不等式 dist[y] <= dist[x] + w 非常相似，因此可以尝试使用**差分约束**建图来完成此题

为满足条件1，从i - 1 向 i 连接一条 权值为0的边，0 - > 1 -> 2 - > 3 … 50001因此源点0是可以到达所有边的。

题目中ai,bi 从0开始的，因此用0来作为源点。

由于求的是最小值，因此求一遍最长路就行了，结果为dist[50001]。	

### 算法设计

```java
import java.util.*;

/**
 * @author MYH
 * @date 2022-12-02
 */
public class P1201 {

    // the distance from zero to index
    static int[] dis = new int[50009];
    // the end point of the idxth edge
    static int[] e = new int[150009];
    // the weight of edge
    static int[] w = new int[150009];
    // find the next idx
    static int[] ne = new int[150009];
    // Record the index of the last edge starting with a
    static int[] h = new int[150009];
    static int idx;

    static void add(int a,int b,int c){
        e[idx] = b;
        w[idx] = c;
        ne[idx] = h[a];
        h[a] = idx++;
    }

    static void spfa(){
        Arrays.fill(dis,-0x3f);
        dis[0] = 0;
        Queue<Integer> queue = new LinkedList<Integer>();
        Set<Integer> set = new HashSet<Integer>();
        queue.offer(0);
        set.add(0);
        while(queue.size()!=0){
            int cur = queue.poll();
            set.remove(cur);
            for(int i = h[cur];i>=0;i=ne[i]){
                int j = e[i];
                if(dis[j] < dis[cur] + w[i]){
                    dis[j] = dis[cur] + w[i];
                    if(!set.contains(j)){
                        set.add(j);
                        queue.offer(j);
                    }
                }
            }
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        idx = 0;
        Arrays.fill(h,-1);
        for(int i = 0;i < 50001;i++){
            add(i,i+1,0);
            add(i+1,i,-1);
        }
        for(int i = 0;i < n;i++){
            add(scan.nextInt(),scan.nextInt()+1,scan.nextInt());
        }
        spfa();
        System.out.println(dis[50001]);
    }
}
```

1. 数据处理

   根据对题目的分析，使用差分约束来解决这个问题，首先需要建立有向带权图，用数组e存取第i条边的终点，数组w存取第i条边的权值(即ci)，数组ne存取以a为起点的上一条边的索引i，数组h存取以a为起点的最后一条边的索引i，通过这种存取方式，可以快速遍历所有以a为起点的边，加快运行速度

2. spfa

   spfa是求单源最短路径的一种算法，它是Bellman-ford的队列优化，建立一个队列，初始时队列里只有起始点，在建立一个表格记录起始点到所有点的最短路径（该表格的初始值要赋为极大值，该点到他本身的路径赋为0）。然后执行松弛操作，用队列里有的点去刷新起始点到所有点的最短路，如果刷新成功且被刷新点不在队列中则把该点加入到队列最后。重复执行直到队列为空。

### 性能分析

- 时间复杂度

  spfa算法的最差时间复杂度为O(VE)，其中V为定值50000，E为100000+n，初始化图的时间复杂度为常数O(1)，读取数据的时间复杂度为O(n)

- 空间复杂度

  由题目知，n的范围为[1,50000]，对于每组数据，需要4个空间来存储建图相关的数据，除此之外初始化时使用了400000大小的空间来对图进行初始化，同时因为a,b的范围为[1,50000]需要大小为50000的数组dis来存储每个点与源点的距离，同时还有queue以及set所占空间，但其空间重复利用程度高，所占空间相对数组较小，综合考虑空间复杂度为O(n)

### 运行测试

## *POJ3040

### 题目分析

典型的贪心算法，每一次发工资，都要考虑当前所能实现的最优策略。
对coin数组按照面值大小从小到大排序，然后将数值大于等于C的先提前计算。
为了能最大程度实现每次发的工资都尽可能贴近C，我们需要先从大到小进行分配，分配过程中，费用不能超过C；然后，如果费用不等于C，也就是仍然需要面值小的进行补偿，就需要从小到大进行分析，这时的费用可以超过C，因为是从小到大，我们可以将小面值用到极致，也就是能用的都用了。
贪心过程需要used数组记录每一个面值所使用的数目，这样就可以找到最优组合可以实现多少次，也就是coin[i].num/used[i]中的最小值。
当搭配完毕后，若出现费用仍然大于零的情况，就说明当前的钱不够分工资了，退出循环。

### 算法设计

### 性能分析

- 时间复杂度
- 空间复杂度

### 运行测试

## 实验总结

### Presentation error

OJ对输出的结果要求相对比较严格，一个空格的不正确抑或是换行符错误都会导致不通过，对于长字符串的输出，应该直接复制题目中的输出并进行修改，而不是手动去输入

### recursion

递归过程出现多个结束条件判断时，需要缜密**选择判断的先后顺序**，例如在POJ1753 Flip Game中，递归的判断条件有1. 遍历完所有点 2. 达成目标，由于判断达成目标语句判断的是上一次递归结束后的结果，所以应该放在前面，这样才能得到正确的输出结果

### 方法传参为数组

Java中将数组作为参数传入时，传入的是地址，在其中对数据进行操作会改变原数组，如果想要不影响原数组，可以使用Arrays.copyOf()来获得一个与传入数组值相同的新数组，在新数组上进行修改。

