import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int[][] room = new int[n][2];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            room[i][0] = Integer.parseInt(tokenizer.nextToken());
            room[i][1] = Integer.parseInt(tokenizer.nextToken());
        }
        in.readLine();
        int[][][] dp = new int[n + 1][k + 1][3];
        for(int[][] a : dp){
            for(int[] b : a){
                Arrays.fill(b, -1);
            }
        }
        Arrays.fill(dp[0][k], 0);
        for (int i = 1; i < dp.length; i++) {
            for (int k1 = 0; k1 < dp[i].length; k1++) {
                for (int state = 0; state < dp[i][k1].length; state++) {
                    if ((k1 + (state > 0 ? 1 : 0)) > k)
                        continue;
                    for (int state2 = 0; state2 < dp[i - 1][k1].length; state2++) {
                        if ((state | state2) == 3)
                            continue;
                        dp[i][k1][state] = Math.max(dp[i - 1][k1 + (state > 0 ? 1 : 0)][state2], dp[i][k1][state]);
                    }
                    if(dp[i][k1][state] == -1) continue;
                    for (int b = 0; b < 2; b++) {
                        if ((state & (1 << b)) == 0)
                            dp[i][k1][state] += room[i - 1][b];
                    }
                }
            }
        }
        int max = 0;
        for (int i = 0; i < dp[n][0].length; i++) {
            max = Math.max(max, dp[n][0][i]);
        }
        System.out.println(max);
        in.close();
    }
}