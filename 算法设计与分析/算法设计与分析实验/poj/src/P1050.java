import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-23
 */
public class P1050 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[][] sum = new int[n+1][n+1];
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                sum[i][j] = scan.nextInt();
                sum[i][j] += sum[i-1][j];
            }
        }
        int ans = Integer.MIN_VALUE;
        for(int i = 1;i <= n;i++){
            for(int j = i;j <= n;j++){
                int last = 0;
                for(int k = 1;k <= n;k++){
                    last = Math.max(last,0)+sum[j][k]-sum[i-1][k];
                    ans = Math.max(ans,last);
                }
            }
        }
        System.out.println(ans);
    }
}
