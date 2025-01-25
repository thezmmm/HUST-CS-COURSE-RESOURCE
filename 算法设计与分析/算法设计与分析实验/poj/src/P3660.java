import java.util.Arrays;
import java.util.Scanner;

/**
 * @author MYH
 * @date  2022-11-29
 */
public class P3660 {

    static boolean[] record;

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int m = scan.nextInt();
        int[][] results = new int[m][2];
        record = new boolean[n];
        for(int i = 0;i < m;i++){
            results[i][0] = scan.nextInt()-1;
            results[i][1] = scan.nextInt()-1;
        }
        int ans = 0;
        for(int i = 0;i < n;i++){
            Arrays.fill(record,false);
            dfs1(results,i);
            int count1 = count();
            Arrays.fill(record,false);
            dfs2(results,i);
            int count2 = count();
            int count = count1 + count2;
            if(count == n-1) ans++;
        }
        System.out.println(ans);

    }
    static void dfs1(int[][] results,int i){
        for(int[] result:results){
            if(result[0] == i && !record[result[1]]){
                record[result[1]] = true;
                dfs1(results,result[1]);
            }
        }
    }
    static void dfs2(int[][] results,int i){
        int ans = 1;
        for(int[] result:results){
            if(result[1] == i&&!record[result[0]]){
                record[result[0]] = true;
                dfs2(results,result[0]);
            }
        }
    }

    static int count(){
        int ans = 0;
        for(boolean b:record){
            if(b) ans++;
        }
        return ans;
    }
}
