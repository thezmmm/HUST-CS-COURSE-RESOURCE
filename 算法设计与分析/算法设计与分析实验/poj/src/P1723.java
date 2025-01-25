import java.util.*;

/**
 * @author MYH
 * @date 2022-11-26
 */
public class P1723 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        List<Position> positions = new ArrayList<Position>();
        for(int i = 0;i < n;i++){
            Position position = new Position(scan.nextInt(),scan.nextInt());
            positions.add(position);
        }
        Collections.sort(positions, (o1, o2) -> o1.y-o2.y);
        int midY = positions.get(n/2).y;
        Collections.sort(positions, (o1, o2) -> o1.x-o2.x);
        for(int i = 0;i < n;i++){
            Position position = positions.get(i);
            position.x -= i;
        }
        Collections.sort(positions, (o1, o2) -> o1.x-o2.x);
        int midX = positions.get(n/2).x;
        int sum = 0;
        for(int i = 0;i < n;i++){
            Position position = positions.get(i);
            sum += Math.abs(position.y-midY);
            sum += Math.abs(position.x-midX);
        }
        System.out.println(sum);

    }

    static class Position{
        int x;
        int y;
        Position(int x,int y){
            this.x = x;
            this.y = y;
        }

    }
}
