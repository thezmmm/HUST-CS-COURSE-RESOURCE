import java.util.*;

/**
 * @author MYH
 * @date 2022-11-27
 */
public class P3579 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        while(scan.hasNext()){
            int n = scan.nextInt();
            int[] list = new int[n];
            for(int i = 0;i < n;i++){
                list[i] = scan.nextInt();
            }
            Arrays.sort(list);
            int m = (n*(n-1)/2)/2;
            int ans = -1;
            int l=0,r=list[n-1]-list[0];
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(check(mid,list,m))
                {
                    r = mid-1;
                    ans = mid;
                }
                else{
                    l = mid+1;
                }
            }
            System.out.println(ans);
        }
    }


    public static int lower_bound(int[] list, int l, int r, int tar) {
        while(l < r){
            int mid = (l+r)/2;
            if(list[mid] <= tar){
                l = mid+1;
            }else{
                r = mid;
            }
        }
        if(list[l] <= tar){
            return l+1;
        }
        return l;
    }

    private static boolean check(int val,int[] list,int m){
        int cnt=0;
        int n = list.length;
        for(int i=0;i<n;i++)
        {
            cnt+=lower_bound(list,i,n-1,list[i]+val)-i-1;
        }
        // >
        cnt = n*(n-1)/2 - cnt;
        if(cnt<=m)
        {
            return true;
        }
        return false;
    }
}