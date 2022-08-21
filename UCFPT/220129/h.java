import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        long[][] ncr = new long[61][61];
        ncr[0][0] = 1;
        for (int i = 0; i + 1 < ncr.length; i++) {
            for (int j = 0; j <= i; j++) {
                ncr[i + 1][j + 1] += ncr[i][j];
                ncr[i + 1][j] += ncr[i][j];
            }
        }
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            int left = k - 1;
            int right = n - k;
            long num = (ncr[left * 2][left] / (left + 1)) * (ncr[right * 2][right] / (right + 1));
            long denom = ncr[n * 2][n] / (n + 1);
            long gcd = gcd(num, denom);
            num /= gcd;
            denom /= gcd;
            System.out.println(num + "/" + denom);
        }
        in.close();
        out.close();
    }

    public static long gcd(long a, long b) {
        if (a < b)
            return gcd(b, a);
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
}