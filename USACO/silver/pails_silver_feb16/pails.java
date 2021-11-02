/*
ID: ssk49881
LANG: JAVA
TASK: pails
*/

import java.io.*;
import java.util.*;

public class pails {
    public static int x;
    public static int y;
    public static int k;
    public static int m;
    public static int[][] dp;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("pails.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("pails.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        x = Integer.parseInt(tokenizer.nextToken());
        y = Integer.parseInt(tokenizer.nextToken());
        k = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        dp = new int[x + 1][y + 1];
        for (int[] i : dp) {
            Arrays.fill(i, -1);
        }
        dfs(0, 0, 0);
        int minDiff = Integer.MAX_VALUE;
        for (int i = 0; i < dp.length; i++) {
            for (int j = 0; j < dp[i].length; j++) {
                if (dp[i][j] != -1 && dp[i][j] <= k && Math.abs(i + j - m) < minDiff) {
                    minDiff = Math.abs(i + j - m);
                }
            }
        }
        out.println(minDiff);

        in.close();
        out.close();
    }

    public static void dfs(int x1, int y1, int depth) {
        if (depth > k) {
            return;
        }
        if (dp[x1][y1] == -1 || depth < dp[x1][y1]) {
            // System.out.println(x1 + " " + y1 + " " + depth);
            dp[x1][y1] = depth;
            if (x1 != x) {
                dfs(x, y1, depth + 1);
            }
            if (y1 != y) {
                dfs(x1, y, depth + 1);
            }
            if (x1 > 0) {
                dfs(0, y1, depth + 1);
            }
            if (y1 > 0) {
                dfs(x1, 0, depth + 1);
            }
            int x2 = Math.min(x, x1 + y1);
            int y2 = y1 - (x2 - x1);
            if (!(x1 == x2 && y1 == y2)) {
                dfs(x2, y2, depth + 1);
            }
            y2 = Math.min(y, x1 + y1);
            x2 = x1 - (y2 - y1);
            if (!(x1 == x2 && y1 == y2)) {
                dfs(x2, y2, depth + 1);
            }
        }
        return;
    }
}