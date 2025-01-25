import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-29
 */
public class P2586 {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int s,d;
        while(in.hasNextInt()){
            s = in.nextInt();
            d = in.nextInt();
            int[] month;
            month = new int[12];
            for (int j=0;j<12;j++)
                month[j] = 0;
            int scount=0,dcount=0;
            for (int i=0;i<8;i++){
                while(true){
                    dcount = month[i]+month[i+1]+month[i+2]+month[i+3]+month[i+4];
                    scount = 5 - dcount;
                    if (s*scount >= d*dcount){
                        for(int k = i+4;k>=0;k--){
                            if (month[k]==0){
                                month[k] =1;
                                break;
                            }
                        }
                    }
                    else
                        break;
                }
            }
            dcount =0;
            for (int i=0;i<12;i++){
                dcount +=month[i];}
            scount =12 - dcount;
            int ans;
            ans = s*scount -d*dcount;
            if(ans>0)
                System.out.println(ans);
            else
                System.out.println("Deficit");
        }
    }
}