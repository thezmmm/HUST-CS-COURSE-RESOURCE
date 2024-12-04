public class Test {
    public static void main(String args[]){
        // Test createArray()
        int[][] arr = createArray(8);

        // Test printArray()
        printArray(arr);
    }

    /**
     *  创建一个不规则二维数组
     *  第一行row列
     *  第二行row - 1列
     *  ...
     *  最后一行1列
     *	数组元素值都为默认值
     * @param row 行数
     * @return 创建好的不规则数组
     */
    public static  int[][] createArray(int row){
        if(row <= 0) return null;
        int[][] ans = new int[row][];
        for(int i = 0;i < row;i++){
            ans[i] = new int[row-i];
        }
        return ans;
    }

    /**
     * 逐行打印出二维数组，数组元素之间以空格分开
     * @param a
     */
    public static  void printArray(int[][] a){
        for(int i = 0;i < a.length;i++){
            for(int j = 0;j < a[i].length;j++){
                System.out.print(a[i][j]);
            }
            System.out.println();
        }
    }
}
