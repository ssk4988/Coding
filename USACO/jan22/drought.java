import java.io.*;
import java.util.*;

public class drought {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        long mod = 1000000007;
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] h = new int[n];
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;
        long answer = 0;
        for (int i = 0; i < n; i++) {
            h[i] = Integer.parseInt(tokenizer.nextToken());
            min = Math.min(h[i], min);
            max = Math.max(h[i], max);
        }
        while (min >= 0) {
            long[] dp = new long[max + 1];
            long[] prefix = new long[max + 1];
            for (int k = 0; k < prefix.length; k++) {
                prefix[k] = k <= h[0] ? k + 1 : h[0] + 1;
                prefix[k] %= mod;
            }
            for (int i = 1; i < n; i++) {
                dp = new long[max + 1];
                for (int j = 0; j <= h[i]; j++) {
                    dp[j] = prefix[h[i] - j];
                    dp[j] %= mod;
                }
                for (int k = 0; k < prefix.length; k++) {
                    prefix[k] = dp[k];
                    if (k > 0) {
                        prefix[k] += prefix[k - 1];
                    }
                    prefix[k] %= mod;
                }
            }
            answer += dp[0];
            answer %= mod;
            if (n % 2 == 0)
                break;
            for (int i = 0; i < n; i++) {
                h[i]--;
            }
            min--;
        }

        System.out.println(answer);
        in.close();
    }
}