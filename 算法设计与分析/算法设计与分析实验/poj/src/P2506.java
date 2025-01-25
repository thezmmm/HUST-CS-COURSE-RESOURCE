import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class P2506 {
    static Map<Integer,BigInteger> map = new HashMap<>();
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        map.put(0,new BigInteger("1"));
        map.put(1, new BigInteger("1"));
        map.put(2, new BigInteger("3"));
        while(scan.hasNext()){
            int n = scan.nextInt();
            System.out.println(ans(n));
        }
    }
    private static BigInteger ans(int n){
        if(map.containsKey(n)){
            return map.get(n);
        }
        BigInteger bi = ans(n-1).add(ans(n-2).add(ans(n-2)));
        map.put(n,bi);
        return map.get(n);
    }
}
