import java.util.Random;
import java.util.Scanner;

public class Homework {
    public static void main(String args[]){
        countLetter();
        getFiveRandomNumber();
    }

    static void countLetter(){
        Scanner scan = new Scanner(System.in);
        String s = scan.next().toLowerCase();
        int[] count = new int[26];
        for(char c : s.toCharArray()){
            count[c-'a']++;
        }
        for(int i = 0;i < 26;i++){
            System.out.println((char)('a'+i)+": " + count[i]);
        }
    }

    static String[] getFiveRandomNumber(){
        String[] strs = new String[5];
        for(int i = 0;i < 5;i++){
            strs[i] = randomNumber();
        }
        return strs;
    }
    static String randomNumber(){
        Random random = new Random();
        StringBuilder sb = new StringBuilder();
        for(int i = 0;i < 3;i++){
            sb.append((char)('A'+random.nextInt(26)));
        }
        for(int i = 0;i < 4;i++){
            sb.append(random.nextInt(10));
        }
        int i = random.nextInt(1);
//        System.out.println(sb);
        return sb.toString();
    }
}
