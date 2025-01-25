import java.util.*;

/**
 * @author MYH
 * @date 2022-12-01
 */
public class P3040 {

    // the class to record coin
    static class Money{
        // value
        int v;
        // num
        int b;

        Money(int v,int b){
            this.v = v;
            this.b = b;
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int c = scan.nextInt();
        // record all money
        Money[] moneys = new Money[25];
        // record how many ith money be used currently
        int[] used = new int[25];
        int ans = 0;
        // the num of type of money
        int idx = 0;
        for(int i = 0;i < n;i++){
            int v = scan.nextInt();
            int b = scan.nextInt();
            // if just one coin can pay, no need to record
            if(v >= c){
                ans += b;
            }else{
                Money money = new Money(v,b);
                moneys[idx++] = money;
            }
        }
        // sort moneys from small to large
        Arrays.sort(moneys,0,idx, new Comparator<Money>() {
            public int compare(Money o1, Money o2) {
                return o1.v-o2.v;
            }
        });
        while(true){
            // reset used
            Arrays.fill(used,0);
            // rest to pay
            int rest = c;
            // from max to min
            for(int i = idx-1;i >=0;i--){
                int tmp = Math.min(rest/moneys[i].v,moneys[i].b);
                rest -= tmp*moneys[i].v;
                used[i] = tmp;
            }
            // need to pay more
            if(rest != 0){
                // from min to max to avoid waste money
                for(int i = 0;i < idx;i++){
                    if(moneys[i].b != 0 && moneys[i].v >= rest){
                        used[i]++;
                        rest = 0;
                        break;
                    }
                }
            }
            // no enough money pay c
            if(rest != 0){
                break;
            }
            // record current strategy can pay how many weeks
            int minx = Integer.MAX_VALUE;
            for(int i = 0;i < idx;i++){
                if(used[i] != 0){
                    minx = Math.min(minx,moneys[i].b/used[i]);
                }
            }
            ans += minx;
            for(int i = 0;i < idx;i++){
                // sub the number of used money
                moneys[i].b -= minx*used[i];
            }
        }
        // print ans
        System.out.println(ans);

    }
}
