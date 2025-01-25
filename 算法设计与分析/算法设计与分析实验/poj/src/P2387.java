import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-29
 */
public class P2387 {
    static int[][] G = new int[1005][1005];
    static int[] dis = new int[1005];
    static boolean[] vis = new boolean[1005];
    static int n, m;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        m = sc.nextInt();
        n = sc.nextInt();
        int u, v, w;
        for (int i = 0; i < m; i++) {
            u = sc.nextInt();
            v = sc.nextInt();
            w = sc.nextInt();
            if (G[u][v] == 0) {
                G[u][v] = G[v][u] = w;
            } else {
                G[u][v] = G[v][u] = Math.min(G[u][v], w);
            }
        }
        //求1-N的最短路
        init();
        dijkstra(1);
        System.out.println(dis[n]);
    }
    static void init() {
        //设置为无穷大
        Arrays.fill(dis, 0x3f3f3f);
    }
    static void dijkstra(int u) {
        dis[u] = 0;
        PriorityQueue<N> q = new PriorityQueue<N>();
        q.add(new N(0, u));

        while (!q.isEmpty()) {
            u = q.poll().v;
            if (vis[u]) continue; //该点若被访问，就换下一个点

            vis[u] = true; //标记为访问
            for (int v = 1; v <= n; v++) {
                if (!vis[v] && G[u][v] != 0 && dis[v] > dis[u] + G[u][v]) {
                    dis[v] = dis[u] + G[u][v];
                    q.add(new N(dis[v], v));
                }
            }
        }
    }
}
class N implements Comparable<N> {
    int minDis, v;
    public N(int minDis, int v) {
        this.minDis = minDis;
        this.v = v;
    }
    public int compareTo(N o) {
        if (minDis == o.minDis) return v - o.v;
        return minDis - o.minDis;
    }

}
