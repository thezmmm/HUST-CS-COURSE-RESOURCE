import java.util.Scanner;

/**
 * @author MYH
 * @date  2022-11-15
 */
public class P1005 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        for(int i = 0;i < n;i++){
            float x = scan.nextFloat();
            float y = scan.nextFloat();
            double d = Math.sqrt(x*x+y*y);
            double s = Math.PI*d*d/2;
            int year = (int) Math.ceil(s/50);
            System.out.println("Property "+(i+1)+": This property will begin eroding in year "+year+".");
        }
        System.out.println("END OF OUTPUT.");
    }
}
