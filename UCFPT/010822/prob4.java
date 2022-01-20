import java.io.*;
import java.util.*;

public class prob4 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            boolean[][] used = new boolean[m][n];
            for (int i = 0; i < m; i++) {
                String s = in.readLine();
                for (int j = 0; j < n; j++) {
                    used[i][j] = s.charAt(j) == 'X';
                }
            }
            int[][] prefix = new int[m][n];
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    prefix[i][j] += used[i][j] ? 1 : 0;
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (i > 0) {
                        prefix[i][j] += prefix[i - 1][j];
                    }
                    if (j > 0) {
                        prefix[i][j] += prefix[i][j - 1];
                    }
                    if (i > 0 && j > 0) {
                        prefix[i][j] -= prefix[i - 1][j - 1];
                    }
                }
            }
            int k = in.readLine().length();
            int low = 0;
            int high = m;
            while (low < high) {
                int mid = low + (high - low + 1) / 2;
                if (test(prefix, k, mid)) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            System.out.println(low);
        }

        in.close();
        out.close();
    }

    public static boolean test(int[][] prefix, int k, int f) {
        for (int i = 0; i + f - 1 < prefix.length; i++) {
            for (int j = 0; j + k * f - 1 < prefix[i].length; j++) {
                int a = prefix[i + f - 1][j + k * f - 1];
                if (i > 0) {
                    a -= prefix[i - 1][j + k * f - 1];
                }
                if (j > 0) {
                    a -= prefix[i + f - 1][j - 1];
                }
                if (i > 0 && j > 0) {
                    a += prefix[i - 1][j - 1];
                }
                if (a == 0)
                    return true;
            }
        }
        return false;
    }
}