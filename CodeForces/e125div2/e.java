import java.io.*;
import java.util.*;

public class e {
    public static long mod = 998244353;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());

        int e1 = n - 1;
        int e2 = n * (n - 1) / 2 - e1;
        System.out.println(e1 + " " + e2);
        ;
        long[] le1 = new long[k + 1]; // ways to set e1 edges <= l with at least 1 edge = l
        long[] le2 = new long[k + 1]; // ways to set e2 edges >= l
        for (int i = 1; i < le1.length; i++) {
            long curr = exp(i, e1) - exp(i - 1, e1);
            while (curr < 0)
                curr += mod;
            le1[i] = curr;
        }
        for (int i = 1; i < le2.length; i++) {
            long curr = exp(k - i + 1, e2);
            while (curr < 0)
                curr += mod;
            le2[i] = curr;
        }
        System.out.println(Arrays.toString(le1));
        System.out.println(Arrays.toString(le2));
        long ans = 0;
        for (int i = 1; i <= k; i++) {
            ans += le1[i] * le2[i];
            ans %= mod;
        }
        b.append(ans + "\n");

        System.out.print(b);
        in.close();
    }

    public static long exp(int base, int power) {
        long val = 1;
        for (int i = 0; i < power; i++) {
            val *= base;
            if (val >= mod) {
                val %= mod;
            }
        }
        return val;
    }
}