import java.io.*;
import java.util.*;

public class fish {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int s = Integer.parseInt(tokenizer.nextToken());
        int n = Integer.parseInt(tokenizer.nextToken());
        int[][] pref = new int[101][101];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            pref[x][y]++;
        }
        for (int i = 0; i < 101; i++) {
            for (int j = 0; j < 101; j++) {
                if (i > 0) {
                    pref[i][j] += pref[i - 1][j];
                }
                if (j > 0)
                    pref[i][j] += pref[i][j - 1];
                if (i > 0 && j > 0)
                    pref[i][j] -= pref[i - 1][j - 1];
            }
        }
        int ans = 0;
        for (int i = 1; i < 101; i++) {
            for (int j = 1; j < 101; j++) {
                ans = Math.max(ans, pref[Math.min(100, i + s)][Math.min(100, j + s)] - pref[Math.min(100, i + s)][j - 1]
                        - pref[i - 1][Math.min(100, j + s)] + pref[i - 1][j - 1]);
            }
        }
        System.out.println(ans);
        in.close();
    }
}