import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-16
 */
public class P1753 {
    public static int[][] direction = new int[][]{{1,0},{-1,0},{0,1},{0,-1},{0,0}};
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int[][] board = new int[4][4];
//        read data: w->0 b->1
        for(int i = 0;i < 4;i++){
            String c = scan.next();
            for(int j = 0;j < 4;j++){
                if(c.charAt(j) == 'w'){
                    board[i][j] = 0;
                }else{
                    board[i][j] = 1;
                }
            }
        }
//        function test
//        test function flip
//        int[][] newBoard = flip(board,1);
//        for(int i = 0;i < 4;i++){
//            System.out.println(Arrays.toString(newBoard[i]));
//        }
//        test isFinished
//        System.out.println(isFinished(flip(board,0)));
        int ans = dfs(board,0,0);
        System.out.println(ans==17?"Impossible":ans);
    }

    private static int dfs(int[][] board,int cur,int count){
        if(isFinished(board)){
            return count;
        }
        if(cur >= 16){
            return 17;
        }
        // don't flip current node
        int t1 = dfs(board,cur+1,count);
        // flip current node
        flip(board,cur);
        int t2 = dfs(board,cur+1,count+1);
        flip(board,cur);
//        return min flip count
        return Math.min(t1,t2);
    }

//  flip cur node
    private static void flip(int[][] board,int cur){
        // calculate current x and y
        int x = cur/4;
        int y = cur-x*4;
        for(int[] dir:direction){
            // make sure x and y in the range
            if(x+dir[0] >=0 && x+dir[0] < 4 && y+dir[1]>=0 && y+dir[1] < 4){
                board[x+dir[0]][y+dir[1]] ^= 1;
            }
        }
    }
//    judge if there is different number
    private static boolean isFinished(int[][] board){
        int x = board[0][0];
        for(int i = 0;i < 4;i++){
            for(int j = 0;j < 4;j++){
                if(board[i][j] != x) {
                    return false;
                }
            }
        }
        return true;
    }
}
