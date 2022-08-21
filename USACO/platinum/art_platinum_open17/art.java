import java.io.*;
import java.util.*;

public class art {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("art.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("art.out")));
        int n = Integer.parseInt(in.readLine());
        int[][] board = new int[n][n];
        boolean[] first = new boolean[n * n + 1];
        Arrays.fill(first, true);
        int[][] lim = new int[first.length][4]; // i1 j1 i2 j2
        TreeSet<Integer> used = new TreeSet<>();
        for (int[] i : lim) {
            i[0] = i[1] = Integer.MAX_VALUE;
            i[2] = i[3] = -1;
        }
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++) {
                board[i][j] = Integer.parseInt(tokenizer.nextToken());
                if (board[i][j] > 0) {
                    used.add(board[i][j]);
                    lim[board[i][j]][0] = Math.min(lim[board[i][j]][0], i);
                    lim[board[i][j]][1] = Math.min(lim[board[i][j]][1], j);
                    lim[board[i][j]][2] = Math.max(lim[board[i][j]][2], i);
                    lim[board[i][j]][3] = Math.max(lim[board[i][j]][3], j);
                }
            }
        }
        long[][] pref = new long[n][n];
        for (int i = 1; i < first.length; i++) {
            if (lim[i][2] == -1)
                continue;
            for (int i1 = lim[i][0]; i1 <= lim[i][2]; i1++) {
                pref[i1][lim[i][1]]++;
                if (lim[i][3] + 1 < n)
                    pref[i1][lim[i][3] + 1]--;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0)
                    pref[i][j] += pref[i][j - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0)
                    pref[i][j] += pref[i][j - 1];
                if (i > 0)
                    pref[i][j] += pref[i - 1][j];
                if (j > 0 && i > 0)
                    pref[i][j] -= pref[i - 1][j - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] <= 0)
                    continue;
                if (calc(pref, i, j, i, j) > 1)
                    first[board[i][j]] = false;
            }
        }
        if (used.size() == 1)
            first[used.first()] = false;
        int ans = 0;
        for (int i = 1; i < first.length; i++) {
            if (first[i])
                ans++;
        }
        out.println(ans);
        in.close();
        out.close();
    }

    public static long calc(long[][] arr, int i1, int j1, int i2, int j2) {
        long a = arr[i2][j2];
        if (i1 > 0)
            a -= arr[i1 - 1][j2];
        if (j1 > 0)
            a -= arr[i2][j1 - 1];
        if (i1 > 0 && j1 > 0)
            a += arr[i1 - 1][j1 - 1];
        return a;
    }
}