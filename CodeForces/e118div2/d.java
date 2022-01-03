import java.io.*;
import java.util.*;

public class d {
    public static int mod = 998244353;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[] arr = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int[][] dp = new int[n + 5][2];
            for (int i = 0; i < n; i++) {
                if (arr[i] > 0) {
                    add(dp[arr[i] - 1], 1, dp[arr[i] - 1][1]);
                    add(dp[arr[i] - 1], 1, dp[arr[i] - 1][0]);
                }
                add(dp[arr[i] + 1], 0, dp[arr[i] + 1][0]);
                add(dp[arr[i] + 1], 1, dp[arr[i] + 1][1]);
                add(dp[arr[i] + 1], 0, dp[arr[i]][0]); // depends on if arr[i] + 1 is already contained
                if (arr[i] == 1) {
                    add(dp[0], 1, 1);
                }
                if (arr[i] == 0) {
                    add(dp[1], 0, 1);
                }
            }
            // System.out.println(Arrays.toString(dp));
            int sum = 0;
            for (int i = 0; i < dp.length; i++) {
                sum += dp[i][0];
                sum %= mod;
                sum += dp[i][1];
                sum %= mod;
            }
            b.append(sum + "\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static void add(int[] arr, int index, int val) {
        arr[index] += val;
        if (arr[index] >= mod) {
            arr[index] %= mod;
        }
    }
}