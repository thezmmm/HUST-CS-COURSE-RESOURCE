import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-17
 */
public class P2503 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        Map<String,String> map = new HashMap<String, String>();
        String read = scan.nextLine();
        while(!read.equals("")){
            String[] word = read.split(" ");
            map.put(word[1],word[0]);
            read = scan.nextLine();
        }
        while(scan.hasNext()){
            String key = scan.next();
            if(map.containsKey(key)) {
                System.out.println(map.get(key));
            }else{
                System.out.println("eh");
            }
        }

    }
}
