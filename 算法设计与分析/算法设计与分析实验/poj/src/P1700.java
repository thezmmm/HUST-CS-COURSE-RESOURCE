import java.util.Arrays;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-28
 */
public class P1700 {

    public static int[] a=new int[1024];

    public static void main(String[] args) {
        int T;
        Scanner in=new Scanner(System.in);
        T=in.nextInt();
        while((T--)!=0)
        {
            int n=in.nextInt();
            for(int i=0;i<n;i++)
                a[i]=in.nextInt();

            Arrays.sort(a,0,n);

            int i;
            int ans=0;
            for(i=n;i>=4;i-=2)
            {
                //最快和最慢过去，然后最快回来，在和次慢过去，最快回来
                int action1=a[i-1] + a[0] + a[i-2] +a[0];

                //最快和次慢过去，然后最快回来，在次慢和最慢过去，次慢回来
                int action2=a[1] +a[0] + a[i-1]  +a[1];
                ans=ans+ ( (action1 < action2 )? action1:action2);
            }
            if(i==3)
                ans+= a[0]+a[1]+a[2];
            if(i==2)
                ans+=a[1];
            if(i==1)
                ans+=a[0];
            System.out.println(ans);
        }

    }

}