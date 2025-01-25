import java.util.*;

/**
 * @author MYH
 * @date 2022-11-17
 */
public class P2366 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        Set<Integer> set = new HashSet<>();
        int len1 = scan.nextInt();
        for(int i = 0;i < len1;i++){
            set.add(10000-scan.nextInt());
        }
        boolean flag = false;
        int len2 = scan.nextInt();
        for(int i = 0;i < len2;i++){
            if(set.contains(scan.nextInt())){
                flag = true;
            }
        }
        if(flag){
            System.out.println("YES");
        }else{
            System.out.println("NO");
        }
    }

}
