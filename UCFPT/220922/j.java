import java.io.*;
import java.util.*;

public class j {
    public static long ways = 0;
    static ArrayList<Integer> factors;
    static int n;
    static int k;
    static int nf;
    static long m[][] = new long[101][101];
    static long mod = Integer.MAX_VALUE;
    static long ans = 0;
    static long f[] = new long[101];
    static long d = 0;
    static long t = 1;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        k = Integer.parseInt(tokenizer.nextToken());
        f[0] = 1;
        for (int i = 1; i <= 100; i++) {
            m[i][0] = 1;
            m[i][1] = ((eEuclid(i, mod)[1] % mod) + mod) % mod;
            for (int j = 2; j <= 100; j++) {
                m[i][j] = mod(m[i][j - 1] * m[i][1]);
            }
            f[i] = mod(f[i - 1] * m[i][1]);
        }
        if (k <= n) {
            factors = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                if (k % i == 0) {
                    factors.add(i);
                }
            }
            nf = factors.size();
            int[] start = new int[nf];
            ways = 0;
            for (int i = 1; i <= n; i++) {
                t = mod(t * i);
            }

            find(start, nf - 1, 0);
        }

        // find(start, 0, 0);
        ans = mod(t * ans);
        if (ways == 0) {
            System.out.println(0);
        } else {
            System.out.println(ans);
        }

    }

    static long mod(long k) {
        return k % mod;
    }

    static void solve(int[] arr) {
        long denom = 1;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > 0) {
                denom = mod(denom * f[arr[i]]);
                denom = mod(denom * m[factors.get(i)][arr[i]]);
            }
        }
        ans = mod(ans + denom);
    }

    static void find(int[] start, int cur, int sum) {
        if (sum == n) {
            long lcm = 1;
            for (int i = 0; i < start.length; i++) {
                if (start[i] > 0) {
                    lcm = lcm / eEuclid(lcm, factors.get(i))[0] * factors.get(i);
                }
            }
            if (lcm == k) {
                ways++;
                solve(start);
            }

            return;
        }
        for (int i = cur; i >= 0; i--) {
            if (sum + factors.get(i) <= n) {
                start[i]++;
                find(start, i, sum + factors.get(i));
                start[i]--;
            }
        }
    }

    static long[] eEuclid(long a, long b) {
        if (b == 0)
            return new long[] { a, 1, 0 };
        long[] ans = eEuclid(b, a % b);
        long temp = ans[1] - ans[2] * (a / b);
        ans[1] = ans[2];
        ans[2] = temp;
        return ans;
    }
}
