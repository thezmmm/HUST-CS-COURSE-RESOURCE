import java.util.*;

/**
 * @author MYH
 * @date  2022-11-16
 */
public class P3295 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String s = scan.next();
        while(!s.equals("0")){
            if(help(s)){
                System.out.println("tautology");
            }else{
                System.out.println("not");
            }
            s = scan.next();
        }
    }

    // Enumerate each case
    private static boolean help(String str){
        Map<Character,Character> map = new HashMap<Character,Character>();
        char[] b = new char[]{'0','1'};
        for(char p:b){
            map.put('p',p);
            for(char q:b){
                map.put('q',q);
                for(char r:b){
                    map.put('r',r);
                    for(char s:b){
                        map.put('s',s);
                        for(char t:b){
                            map.put('t',t);
                            if(!judge(str,map)){
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    // judge if the str is true
    private static boolean judge(String str,Map<Character,Character> map) {
        for(Map.Entry<Character,Character> entry :map.entrySet()){
            str = str.replace(entry.getKey(), entry.getValue());
        }
        while(str.length() != 1){
            if(str.indexOf("K") != -1) {
                str = str.replace("K11", "1");
                str = str.replace("K10", "0");
                str = str.replace("K01", "0");
                str = str.replace("K00", "0");
            }
            if(str.indexOf("A") != -1) {
                str = str.replace("A11", "1");
                str = str.replace("A10", "1");
                str = str.replace("A01", "1");
                str = str.replace("A00", "0");
            }
            if(str.indexOf("C") != -1) {
                str = str.replace("C11", "1");
                str = str.replace("C10", "0");
                str = str.replace("C01", "1");
                str = str.replace("C00", "1");
            }
            if(str.indexOf("E") != -1) {
                str = str.replace("E11", "1");
                str = str.replace("E10", "0");
                str = str.replace("E01", "0");
                str = str.replace("E00", "1");
            }
            if(str.indexOf("N") != -1){
                str = str.replace("N1","0");
                str = str.replace("N0","1");
            }
        }
        return str.equals("1");
    }
}
