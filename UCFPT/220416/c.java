import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int[][][][][] cost = new int[2][2][][][];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] sizes = new int[4];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                sizes[2 * i + j] = Integer.parseInt(tokenizer.nextToken());
                cost[i][j] = new int[5][5][12];
                for (int k = 0; k < cost[i][j].length; k++) {
                    for (int l = 0; l < cost[i][j][k].length; l++) {
                        Arrays.fill(cost[i][j][k][l], -1);
                    }
                }
            }
        }
        int l = Integer.parseInt(tokenizer.nextToken());
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < sizes[2 * i + j]; k++) {
                    tokenizer = new StringTokenizer(in.readLine());
                    int lower = Integer.parseInt(tokenizer.nextToken()) - 1;
                    int upper = Integer.parseInt(tokenizer.nextToken()) - 1;
                    for (int n = 0; n < cost[i][j][lower][upper].length; n++) {
                        cost[i][j][lower][upper][n] = Integer.parseInt(tokenizer.nextToken());
                    }
                }
            }
        }
        boolean[] black = new boolean[88];
        black[1] = true;
        black[4] = true;
        black[6] = true;
        black[9] = true;
        black[11] = true;
        for (int i = 0; i < black.length; i++) {
            if (black[i] && i + 12 < black.length) {
                black[i + 12] = true;
            }
        }
        tokenizer = new StringTokenizer(in.readLine());
        int[] vals = new int[l];
        for (int i = 0; i < l; i++) {
            vals[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
        }
        int[][] dp = new int[l - 1][5];
        for (int i = 0; i < dp.length; i++) {
            // factors: ascending/descending, no interval
            Arrays.fill(dp[i], -1);
            int interval = vals[i + 1] - vals[i];
            if (interval == 0) {
                for (int j = 0; j < dp[i].length; j++) {
                    dp[i][j] = i == 0 ? 0 : dp[i - 1][j];
                }
                continue;
            }
            int absinterval = Math.abs(interval) - 1;
            boolean b0 = black[vals[i]];
            boolean b1 = black[vals[i + 1]];
            boolean lb = interval < 0 ? b1 : b0;
            boolean rb = interval < 0 ? b0 : b1;
            for (int prev = 0; prev < 5; prev++) {
                for (int next = 0; next < 5; next++) {
                    int lower = interval < 0 ? next : prev;
                    int higher = interval < 0 ? prev : next;

                    if (cost[lb ? 1 : 0][rb ? 1 : 0][lower][higher][absinterval] != -1) {
                        if (i == 0 || dp[i - 1][prev] != -1) {
                            int ans = cost[lb ? 1 : 0][rb ? 1 : 0][lower][higher][absinterval];
                            if (i > 0)
                                ans += dp[i - 1][prev];
                            if (dp[i][next] == -1 || ans < dp[i][next]) {
                                dp[i][next] = ans;
                            }
                        }
                    }
                }
            }
        }
        int minCost = Integer.MAX_VALUE;
        for (int i = 0; i < dp[dp.length - 1].length; i++) {
            minCost = Math.min(dp[dp.length - 1][i], minCost);
        }
        System.out.println(minCost);
        in.close();
        out.close();
    }
}