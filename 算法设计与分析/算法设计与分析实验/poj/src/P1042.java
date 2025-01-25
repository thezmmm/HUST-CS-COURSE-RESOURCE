import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-28
 */
public class P1042 {
    static int n,h;
    static int []t = new int[30];
    static int []f = new int[30];
    static int []d = new int[30];
    static int []ans = new int[30];
    public static void main(String str[]){
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()){
            n = cin.nextInt();
            if(n==0) break;
            h = cin.nextInt();
            h*=60;
            int i,j;
            for(i=1;i<=n;i++) f[i] = cin.nextInt();
            for(i=1;i<=n;i++) d[i] = cin.nextInt();
            for(i=1;i<n;i++) t[i] = cin.nextInt();
            int sum = -1;
            for(i=1;i<=n;i++){
                int point = 0,temp_h=h,temp_sum=0;
                int []temp_f = new int[30];
                int []temp_ans = new int[30];
                for(j=1;j<=n;j++) temp_f[j] = f[j];
                while(temp_h!=0){
                    int maxf = 0;
                    for(j=1;j<=i;j++){
                        if(temp_f[j]>maxf){
                            maxf = temp_f[j];
                            point = j;
                        }
                    }
                    if(maxf!=0){
                        temp_ans[point] += 5;
                        temp_sum += temp_f[point];
                        if(temp_f[point] >= d[point])
                            temp_f[point] -= d[point];
                        else
                            temp_f[point] = 0;
                    }
                    else{
                        temp_ans[1] +=temp_h;
                        break;
                    }
                    temp_h -=5;
                }
                if(h>t[i]*5) h-=t[i]*5;
                else h = 0;
                if(temp_sum>sum){
                    for(j = 1;j <= n;j++)
                        ans[j] = temp_ans[j];
                    sum = temp_sum;
                }
            }
            for(i=1;i<n;i++) System.out.print(ans[i]+", ");
            System.out.println(ans[n]);
            System.out.println("Number of fish expected: "+sum);
            System.out.println();
        }
    }
}
