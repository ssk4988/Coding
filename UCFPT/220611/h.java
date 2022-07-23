import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int h = Integer.parseInt(tokenizer.nextToken());
        int s = Integer.parseInt(tokenizer.nextToken());
        long[][] dp = new long[h + 1][s + 1];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int h1 = Integer.parseInt(tokenizer.nextToken());
            int s1 = Integer.parseInt(tokenizer.nextToken());
            long w = Long.parseLong(tokenizer.nextToken());
            for (int j = 0; j < dp.length; j++) {
                for (int k = 0; k < dp[j].length; k++) {
                    if (j - h1 > 0) {
                        if (k - s1 >= 0) {
                            dp[j - h1][k - s1] = Math.max(dp[j - h1][k - s1], dp[j][k] + w);
                        } else if (j - h1 + (k - s1) > 0) {
                            dp[j - h1 + k - s1][0] = Math.max(dp[j - h1 + k - s1][0], dp[j][k] + w);
                        }
                    }
                }

            }
        }
        long max = 0;
        for (int i = 1; i < dp.length; i++) {
            for (int j = 0; j < dp[i].length; j++) {
                max = Math.max(max, dp[i][j]);
            }

        }
        System.out.println(max);
        in.close();
    }
}