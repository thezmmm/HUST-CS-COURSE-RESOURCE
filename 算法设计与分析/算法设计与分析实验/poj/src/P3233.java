
import java.io.BufferedInputStream;
import java.util.Scanner;

/**
 * @author MYH
 * @date 2022-11-23
 */
public class P3233 {
    static Scanner in = new Scanner(new BufferedInputStream(System.in));
    static long mod;

    static class Mat {
        public long a[][];
        public int x;

        public Mat(int x) {
            a = new long[x][x];
            this.x = x;
        }

        public Mat mu(Mat t) {
            Mat ans = new Mat(x);
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < x; j++) {
                    for (int k = 0; k < x; k++) {
                        ans.a[i][j] += a[i][k] * t.a[k][j];
                    }
                    ans.a[i][j] %= mod;
                }
            }
            return ans;
        }

        public Mat add(Mat t) {
            Mat ans = new Mat(x);
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < x; j++) {
                    ans.a[i][j] = (a[i][j] + t.a[i][j]) % mod;
                }
            }
            return ans;
        }

        public Mat() {
            super();
        }

    }

    static Mat E;

    static void setE(int s) {
        E = new Mat(s);
        for (int i = 0; i < s; i++)
            E.a[i][i] = 1;
    }

    static Mat Z;

    static void setZ(int s) {
        Z = new Mat(s);
    }

    static Mat A;

    static void setA(int s) {
        A = new Mat(s);
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                A.a[i][j] = in.nextLong() % mod;
            }
        }
    }

    static class M {
        public Mat a[][];

        public M() {
            a = new Mat[2][2];
        }

        public void set(Mat t, Mat b, Mat c, Mat d) {
            a[0][0] = t;
            a[0][1] = b;
            a[1][0] = c;
            a[1][1] = d;
        }

        public M mu(M t) {
            M ans = new M();
            ans.a[0][0] = E;
            ans.a[1][0] = Z;
            ans.a[0][1] = t.a[0][1].add(a[0][1].mu(t.a[1][1]));
            ans.a[1][1] = a[1][1].mu(t.a[1][1]);
            return ans;
        }
    }

    static M x;
    static M e;

    static M pow(int t) {
        M ans = e;
        while (t > 0) {
            if ((t & 1) == 1) {
                ans = ans.mu(x);
            }
            x = x.mu(x);
            t >>= 1;
        }
        return ans;
    }

    static Mat ans;

    public static void main(String[] args) {
        x=new M();
        e=new M();
        while(in.hasNext()) {
            int n=in.nextInt(),k=in.nextInt();
            mod=in.nextLong();
            setE(n);setZ(n);setA(n);
            x.set(E, A, Z, A);
            e.set(E, Z, Z, E);
            ans=pow(k).a[0][1];
            for(int i=0;i<n;i++) {
                for(int j=0;j<n;j++) {
                    if(j!=0)System.out.print(" ");
                    System.out.print(ans.a[i][j]);
                }
                System.out.println();
            }
        }
    }
}
