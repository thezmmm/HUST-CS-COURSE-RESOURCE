import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * @author MYH
 * @date 2022-11-27
 */
public class P1185 {
    static char[][] info;
    static int[][] transInfo;
    static int[] possibleStatus;
    static int possibleStatusCnt;
    static int[][][] dp;
    static int[] rowInitPosition;

    static int n,m;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        info = new char[n][m];
        transInfo = new int[n][m];
        possibleStatus = new int[100];
        dp = new int[n][100][100];
        rowInitPosition = new int[n];

        initDp();
        initPossibleStatus();

        char[] inputCharArray;
        for(int i = 0;i<info.length;i++){
            inputCharArray = br.readLine().toCharArray();
            info[i] = inputCharArray;
            for(int j = 0;j<info[0].length;j++){
                transInfo[i][j] = inputCharArray[j] == 'P'?1:0;
                rowInitPosition[i] += transInfo[i][j]*(1<<(info[0].length-1-j));
            }
        }

        for(int i = 0;i<possibleStatusCnt;i++){
            if((possibleStatus[i]&rowInitPosition[0]) != possibleStatus[i]){
                continue;
            }
            dp[0][0][i] = getNumberBinaryOneCnt(possibleStatus[i]);
        }

        for(int i=1;i<n;i++){
            for(int j = 0;j<possibleStatusCnt;j++){
                //current row
                if((possibleStatus[j]&rowInitPosition[i]) != possibleStatus[j]){
                    continue;
                }
                for(int k = 0;k<possibleStatusCnt;k++){
                    //current-1 row
                    if(is2RowPositionNotOk(possibleStatus[j], possibleStatus[k])){
                        continue;
                    }
                    for(int p = 0;p<possibleStatusCnt;p++){
                        //current-2 row
                        if(is2RowPositionNotOk(possibleStatus[j], possibleStatus[p])){
                            continue;
                        }
                        if(dp[i-1][k][p] == -1){
                            continue;
                        }
                        dp[i][p][j] = Math.max(dp[i][p][j],dp[i-1][k][p]+getNumberBinaryOneCnt(possibleStatus[j]));
                    }
                }
            }
        }

        int result = 0;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<possibleStatusCnt;j++){
                for(int k = 0;k<possibleStatusCnt;k++){
                    result = Math.max(result,dp[i][j][k]);
                }
            }
        }
        System.out.println(result);
    }

    private static void initPossibleStatus(){
        possibleStatusCnt = 0;
        for(int i = 0;i<(1<<m);i++){
            if((i&(i<<1)) == 0 && (i&(i<<2)) == 0){
                possibleStatus[possibleStatusCnt] = i;
                possibleStatusCnt++;
            }
        }
    }

    private static void initDp(){
        for (int[][] ints : dp) {
            for (int[] anInt : ints) {
                Arrays.fill(anInt, -1);
            }
        }
    }

    private static boolean is2RowPositionNotOk(int x, int y){
        return (x & y) != 0;
    }

    private static int getNumberBinaryOneCnt(int num){
        int cnt = 0;
        while (num != 0){
            num = (num&(num-1));
            cnt++;
        }
        return cnt;
    }
}

