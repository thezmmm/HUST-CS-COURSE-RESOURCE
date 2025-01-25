import java.util.*;

/**
 * @author MYH
 * @date 2022-11-27
 */
public class P3269 {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        List<Position> positions = new ArrayList<Position>();
        for(int i = 0;i < n;i++){
            Position position = new Position(scan.nextInt(),scan.nextInt());
            positions.add(position);
        }
        Collections.sort(positions, new Comparator<Position>() {
            @Override
            public int compare(Position o1, Position o2) {
                return o1.y-o2.y;
            }
        });
        int midY = positions.get(n/2).y;
        int minY = positions.get(n/2-1).y;
        int maxY = positions.get(n/2).y;
        Collections.sort(positions, new Comparator<Position>() {
            @Override
            public int compare(Position o1, Position o2) {
                return o1.x-o2.x;
            }
        });
        int midX = positions.get(n/2).x;
        int minX = positions.get(n/2-1).x;
        int maxX = positions.get(n/2).x;
        int sum = 0;
        int count = (maxX-minX+1)*(maxY-minY+1);
        for(int i = 0;i < n;i++){
            Position position = positions.get(i);
            if(position.x>=minX&&position.y<=maxY&&position.x<=maxX&&position.y>=minY){
                count--;
            }
            sum += Math.abs(position.y-midY);
            sum += Math.abs(position.x-midX);
        }
        if(n%2 != 0){
            sum = Integer.MAX_VALUE;
            count = 0;
            int[][] directions = new int[][]{{0,1},{0,-1},{1,0},{-1,0}};
            for(int[] direction : directions){
                int x = midX + direction[0];
                int y = midY + direction[1];
                int s = 0;
                for(Position position : positions){
                    s += Math.abs(position.x - x);
                    s += Math.abs(position.y - y);
                }
                if(s < sum){
                    sum = s;
                    count = 1;
                }else if(s == sum){
                    count++;
                }
            }
        }
        System.out.println(sum+" "+count);

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
