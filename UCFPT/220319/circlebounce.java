import java.io.*;
import java.util.*;

public class circlebounce {
    static long modint = 1000000007;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        long a = Integer.parseInt(tokenizer.nextToken());
        long b = Integer.parseInt(tokenizer.nextToken());
        long n = Long.parseLong(tokenizer.nextToken()) + 1;
        long c = a * a + b * b;
        long[] inv = gcd(c, modint);
        long invc = inv[0];
        long[][] matrix = new long[2][2];
        matrix[0][0] = matrix[1][1] = mod(a * a - b * b);
        matrix[0][1] = mod(2 * a * b);
        matrix[1][0] = mod(-2 * a * b);
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                matrix[i][j] = mod(matrix[i][j] * invc);
            }
        }
        long[][] res = pow(matrix, n);
        System.out.println(mod(-res[0][0]));
        in.close();
        out.close();
    }

    public static long[] gcd(long a, long b) {
        if (b == 0) {
            return new long[] { 1, 0 };
        }
        long[] arr1 = gcd(b, a % b);
        long[] ans = new long[] { arr1[1], arr1[0] - (a / b) * arr1[1] };
        return ans;
    }

    public static long[][] matmul(long[][] a, long[][] b) {
        long[][] res = new long[a.length][b[0].length];
        for (int i = 0; i < res.length; i++) {
            for (int j = 0; j < res[i].length; j++) {
                for (int k = 0; k < b.length; k++) {
                    res[i][j] = mod(res[i][j] + mod(a[i][k] * b[k][j]));
                }
            }
        }
        return res;
    }

    public static long mod(long l) {
        return ((l % modint) + modint) % modint;
    }

    public static long[][] pow(long[][] a, long n) {
        if (n == 1)
            return a;
        long[][] res = pow(a, n / 2);
        res = matmul(res, res);
        if (n % 2 == 1)
            res = matmul(res, a);
        return res;
    }
}
