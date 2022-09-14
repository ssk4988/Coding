import java.io.*;
import java.util.*;

public class array {
    public static int n;
    public static int m;
    public static int mod = 1000000007;
    public static boolean[][] calculated;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        int[][] dp = new int[n][m + 1];
        calculated = new boolean[n][m + 1];
        int[] array = new int[n];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            array[i] = Integer.parseInt(tokenizer.nextToken());
        }
        if (array[0] == 0) {
            for (int i = 1; i <= m; i++) {
                dp[0][i] = 1;
            }
        } else {
            dp[0][array[0]] = 1;
        }
        for (int i = 0; i + 1 < n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = Math.max(1, j - 1); k <= Math.min(m, j + 1); k++) {
                    if (array[i + 1] == 0 || k == array[i + 1]) {
                        dp[i + 1][k] += dp[i][j];
                        while (dp[i + 1][k] >= mod) {
                            dp[i + 1][k] -= mod;
                        }
                    }

                }
            }
        }
        int ans = 0;
        for(int i= 1; i <= m; i++){
            ans += dp[n-1][i];
            while(ans >= mod){
                ans -= mod;
            }
        }
        System.out.println(ans);

        in.close();
    }
}