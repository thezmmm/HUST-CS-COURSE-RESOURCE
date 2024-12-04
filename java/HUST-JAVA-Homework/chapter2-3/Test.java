import java.util.Scanner;

public class Test {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int num = scan.nextInt();
        System.out.println(solve(num));
    }

    public static int solve(int num){
        if(num<0 || num > 1000){
            return -1;
        }
        int ans = 0;
        while(num != 0){
            ans += num%10;
            num /= 10;
        }
        return ans;
    }
}