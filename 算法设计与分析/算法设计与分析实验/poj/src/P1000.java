import java.util.Scanner;

public class P1000{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String a = scan.next();
        String b = scan.next();
        System.out.println(Integer.parseInt(a) + Integer.parseInt(b));
        scan.close();
    }
}