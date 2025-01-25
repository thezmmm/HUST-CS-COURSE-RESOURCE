import java.util.Arrays;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-29
 */
public class P1062 {

    static int lim;//等级限制
    static int n;//包括探险家在内的总物品个数
    static int[][] w;//w[i][j]节点i到j的权重
    static int[] lev;//lev[i]物品i的等级
    static int[] p;//p[i]物品i的价值
    static int[] dis;//dis[i]0到i的估计最短权重
    static int[] vis;//标记区间

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        lim = sc.nextInt();
        n = sc.nextInt();
        w = new int[n+1][n+1];
        lev = new int[n+1];
        p = new int[n+1];
        dis = new int[n+1];
        vis = new int[n+1];
        for (int i = 1; i <= n; i++) {
            p[i] = sc.nextInt();
            lev[i] = sc.nextInt();
            int k = sc.nextInt();
            for (int j = 0; j < k; j++) {
                int t = sc.nextInt();
                w[t][i] = sc.nextInt();
            }
        }
        for (int i = 1; i <= n; i++) {
            w[0][i] = p[i];
        }
        solve();
    }

    static int MAX = 0xFFFFFF;
    static void dijkstra(){
        vis[0] = 0;
        Arrays.fill(dis,MAX);
        dis[0] = 0;
        int min = MAX;
        int tmp = 0;
        for (int i = 0; i <= n; i++) {
            min = MAX;
            for (int j = 0; j <= n; j++) {
                if (vis[j]==0&&dis[j]<min){
                    tmp = j;
                    min = dis[j];
                }
            }
            vis[tmp] = 1;
            for (int j = 1; j <= n; j++) {
                if (vis[j]==0&&w[tmp][j]!=0&&dis[j]>dis[tmp]+w[tmp][j]){
                    dis[j] = dis[tmp]+w[tmp][j];
                }
            }
        }
    }

    static void solve(){
        int min = w[0][1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (lev[j]>=lev[i]&&lev[j]<=lim+lev[i]){
                    vis[j] = 0;
                }else {
                    vis[j] = 1;
                }
            }
            if (vis[1]==0){
                dijkstra();
            }
            if (dis[1]<min){
                min = dis[1];
            }
        }
        System.out.println(min);
    }
}