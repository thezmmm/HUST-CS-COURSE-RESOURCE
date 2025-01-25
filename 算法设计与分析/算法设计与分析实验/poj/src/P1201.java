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
