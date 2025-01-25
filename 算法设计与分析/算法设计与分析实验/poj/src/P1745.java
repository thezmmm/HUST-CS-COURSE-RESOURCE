import java.util.*;
/**
 * @author MYH
 * @date 2022-11-29
 */
public class P1745 {

    public static void main(String[] args){
        Scanner scanner=new Scanner(System.in);
        int n,k;
        int [][]dp=new int [10010][110];

        int []a=new int [10010];
        n=scanner.nextInt();
        k=scanner.nextInt();
        for(int i=1;i<=n;i++)
            a[i]=scanner.nextInt();
        dp[1][((a[1])%k+k)%k]=1;
        dp[1][((-a[1])%k+k)%k]=1;
        for(int i=2;i<=n;i++){
            for(int j=0;j<=k;j++){
                if(dp[i-1][((j-a[i])%k+k)%k]==1 || dp[i-1][((j+a[i])%k+k)%k]==1)
                    dp[i][j]=1;
            }
        }
        if(dp[n][0]==1)
        {System.out.print("Divisible\n");

        }
        else
        {
            System.out.print("Not divisible\n");

        }
    }
}

