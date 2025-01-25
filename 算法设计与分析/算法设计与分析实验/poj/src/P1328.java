import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;
/**
 * @author MYH
 * @date 2022-11-28
 */
public class P1328
{
    static int n;//岛屿的个数
    static int d;//雷达的覆盖半径
    static float map[][];//n个岛屿的位置
    static boolean flag = false;
    int ans;

    void init()
    {
        map = new float [n][2];
        ans = 0;
    }

    //升序排序
    public static void sort(float[][] ob, final int[] order) {
        Arrays.sort(ob, new Comparator<Object>() {
            public int compare(Object o1, Object o2) {
                float[] one = (float[]) o1;
                float[] two = (float[]) o2;
                for (int i = 0; i < order.length; i++) {
                    int  k = order[i];
                    if (one[k] > two[k]) {
                        return 1;
                    } else if (one[k] < two[k]) {
                        return -1;
                    } else {
                        continue;  //如果按一条件比较结果相等，就使用第二个条件进行比较。
                    }
                }
                return 0;
            }
        });
    }


    int  greedy()
    {
        int num = 0;
        float cur;

        cur = map[0][1];
        num++;

        for(int i=1; i<n; i++)
        {
            if(map[i][0] > cur)
            {
                num++;
                cur = map[i][1];
            }
            else
            {
                if(map[i][1] < cur)
                    cur = map[i][1];
            }

        }
        return num;
    }

    void output(int k)
    {
        if(flag)
        {
            System.out.println("Case " + k + ": " + -1);
        }
        else     //刚开始这个地方没有加else导致如果flag=true时则 输出两遍结果
        {
            ans = greedy();
            System.out.println("Case " + k + ": " + ans);
        }

    }

    public static void main(String args[])
    {
        int k = 0;

        Scanner cin = new Scanner(System.in);

        n = cin.nextInt();
        d = cin.nextInt();
        P1328 ri = new P1328();

        while(n != 0 && d != 0)
        {
            k++;

            ri.init();

            for(int i=0; i<n; i++)
            {
                float x;
                float y;

                x = cin.nextFloat();
                y = cin.nextFloat();

                if(y > d)
                {
                    flag = true;
                }

                float tmp = (float)(Math.sqrt(d*d - y*y));
                map[i][0] = x - tmp;
                map[i][1] = x + tmp;

            }
            sort(map, new int[] {0}); //以第0列为关键字作升序排序
            ri.output(k);

            n = cin.nextInt();
            d = cin.nextInt();
            flag = false;
        }
        cin.close();
    }
}