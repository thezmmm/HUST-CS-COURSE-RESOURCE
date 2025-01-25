import java.text.DecimalFormat;
import java.util.*;

public class P3714 {
    static Point[] point = new Point[100005];
    static Point[] temp = new Point[1000005];

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        DecimalFormat df = new DecimalFormat("0.000");
        int count = scan.nextInt();
        for (int t = 0; t < count; t++) {
            int n = scan.nextInt();
            for (int i = 0; i < n; i++) {
                Point p = new Point(scan.nextDouble(), scan.nextDouble(), 0);
                point[i] = p;
            }
            for (int i = n; i < n * 2; i++) {
                Point p = new Point(scan.nextDouble(), scan.nextDouble(), 1);
                point[i] = p;
            }
            for (int i = 0; i < 2 * n - 1; i++) {
                for (int j = 0; j < 2 * n - 1 - i; j++) {
                    if (point[j].x > point[j + 1].x) {
                        Point p = point[i];
                        point[i] = point[j];
                        point[j] = p;
                    }
                }
            }
            System.out.println(df.format(merge(0, n)));
        }
    }

    public static class Point {
        double x;
        double y;
        int flag;

        Point(double x, double y, int flag) {
            this.x = x;
            this.y = y;
            this.flag = flag;
        }
    }

    private static double dist(Point p1, Point p2) {
        if (p1.flag == p2.flag) {
            return Double.MAX_VALUE;
        }
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    static double merge(int l, int r) {
        //边界条件
        //左右相等，两点同性质返回inf
        //两点不同性质返回距离
        if (l == r)
            return Double.MAX_VALUE;
        if (l + 1 == r) {
            if (point[l].flag == point[r].flag)
                return Double.MAX_VALUE;
            else
                return dist(point[l], point[r]);
        }
        //分治求解
        int mid = (l + r) >> 1;
        double ll = merge(l, mid);
        double rr = merge(mid + 1, r);
        //求解当前最小dist
        double ans = Math.min(ll, rr);
        //合并中间dist的条件一定为距离边界小于dist的值
        //k记录当前的小于ans的中间值有多少
        int i, j, k = 0;
        for (i = l; i <= r; i++) {
            if (Math.abs(point[i].x - point[mid].x) <= ans)
                temp[++k] = point[i];
        }
        //暴力枚举求解
        for (i = 0; i < k-1; i++) {
            for (j = 0; j < k - 1 - i; j++) {
                if (point[j].x > point[j + 1].x) {
                    Point p = point[i];
                    point[i] = point[j];
                    point[j] = p;
                }
            }
        }
        for (i = 1; i <= k; i++)
            for (j = i + 1; j <= k; j++) {
                //如果当前排序的距离已经大于了当前最小答案，肯定不符合要求
                if (temp[j].y - temp[i].y > ans)
                    break;
                //否者直接更新
                if (temp[i].flag != temp[j].flag)
                    ans = Math.min(ans, dist(temp[i], temp[j]));
            }
        return ans;
    }

}