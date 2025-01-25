import java.util.Arrays;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-29
 */
public class P1860 {

    Scanner cin = new Scanner(System.in);
    int  v, e, sour;
    double startMoney;
    Edge[] eEdgeInfo;
    double[] dDistance;

    public void input()
    {
        int k =0;
        int a,b;
        double rab,cab,rba,cba;
        //System.out.println("输入问题初始化数据");
        v =cin.nextInt();
        e = cin.nextInt();
        sour = cin.nextInt();
        startMoney = cin.nextDouble();
        eEdgeInfo = new Edge[e*2];
        dDistance = new double[v+2];
        Arrays.fill(dDistance, 0);
        dDistance[sour] = startMoney;

        for (int i = 0; i < e; i++) {
            a = cin.nextInt();
            b = cin.nextInt();
            rab = cin.nextDouble();
            cab = cin.nextDouble();
            rba = cin.nextDouble();
            cba = cin.nextDouble();
            eEdgeInfo[k] = new Edge();
            eEdgeInfo[k].a =a;
            eEdgeInfo[k].b = b;
            eEdgeInfo[k].rate = rab;
            eEdgeInfo[k].commission = cab;
            k++;
            eEdgeInfo[k] = new Edge();
            eEdgeInfo[k].a =b;
            eEdgeInfo[k].b =a;
            eEdgeInfo[k].rate = rba;
            eEdgeInfo[k].commission = cba;
            k++;
        }
    }

    public int bellman_Ford() {
        input();
        int nflag = 0;
        int nChange = 0;
        double temp = 0;

        for (int i = 0; i < v-1; i++) {
            nChange = 0;
            for (int j = 0; j < e*2; j++) {
                temp = (dDistance[eEdgeInfo[j].a] - eEdgeInfo[j].commission)*eEdgeInfo[j].rate;
                if (dDistance[eEdgeInfo[j].b] < temp ) {
                    dDistance[eEdgeInfo[j].b] =temp;
                    nChange = 1;

                }
            }
            if (nChange == 0) {
                break;
            }

        }
        for (int j = 0; j < e*2; j++) {
            if (dDistance[eEdgeInfo[j].b] < (dDistance[eEdgeInfo[j].a] - eEdgeInfo[j].commission)*eEdgeInfo[j].rate) {
                nflag = -1;
                break;          //有正权回路

            }
        }


        return nflag;
    }

    public void solve()
    {
        while (cin.hasNext()) {
            int nFlag = bellman_Ford();
            if (nFlag == -1) {
                System.out.println("YES");

            }
            else {
                System.out.println("NO");
            }

        }

    }
    public static void main(String[] args){

        new P1860().solve();

        //System.out.println("输入结束");
    }

    class Edge{
        public int a;
        public int b;
        public double rate;
        public double commission;


    }
}