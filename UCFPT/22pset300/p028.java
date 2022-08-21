import java.io.*;
import java.util.*;

public class p028 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        boolean[][] board = new boolean[n][n];
        int[][] prefix = new int[n][n];
        int choc = 0;
        boolean[] composite = new boolean[5000];
        composite[0] = composite[1] = true;
        TreeSet<Integer> primes = new TreeSet<>();
        for (int i = 2; i < composite.length; i++) {
            if (composite[i])
                continue;
            primes.add(i);
            for (int j = 2 * i; j < composite.length; j += i) {
                composite[j] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            String s = in.readLine();
            for (int j = 0; j < n; j++) {
                board[i][j] = s.charAt(j) == '-';
                if (board[i][j]) {
                    prefix[i][j]++;
                    choc++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0)
                    prefix[i][j] += prefix[i - 1][j];
                if (j > 0)
                    prefix[i][j] += prefix[i][j - 1];
                if (i > 0 && j > 0)
                    prefix[i][j] -= prefix[i - 1][j - 1];
            }
        }
        boolean sq4 = false;
        int minX = Integer.MAX_VALUE;
        int maxX = -1;
        int minY = Integer.MAX_VALUE;
        int maxY = -1;
        for (int i = 0; i < board.length - 1; i++) {
            for (int j = 0; j < board[i].length - 1; j++) {
                if (board[i][j] && board[i + 1][j] && board[i][j + 1] && board[i + 1][j + 1]) {
                    minX = Math.min(i, minX);
                    maxX = Math.max(i + 1, maxX);
                    minY = Math.min(j, minY);
                    maxY = Math.max(j + 1, maxY);
                    sq4 = true;
                }
            }
        }
        boolean elim = false;
        if (!sq4)
            elim = true;
        findelim: for (int x1 = minX; x1 <= minX + 1; x1++) {
            for (int x2 = maxX - 1; x2 <= maxX; x2++) {
                if (x1 > x2)
                    continue;
                for (int y1 = minY; y1 <= minY + 1; y1++) {
                    for (int y2 = maxY - 1; y2 <= maxY; y2++) {
                        if (y1 > y2)
                            continue;
                        if (x2 - x1 != y2 - y1)
                            continue;
                        if (calc(prefix, x1, y1, x2, y2) != (x2 - x1 + 1) * (x2 - x1 + 1))
                            continue;
                        if (x2 - x1 == 1 || !primes.contains(x2 - x1 + 1))
                            continue;
                        elim = true;
                        break findelim;
                    }
                }
            }
        }
        boolean ruby = false;
        if (choc % 2 == 0) {
            ruby = sq4;
        } else {
            ruby = elim;
        }
        System.out.println(ruby ? "RUBY" : "DIA");

        in.close();
    }

    public static int calc(int[][] prefix, int i1, int j1, int i2, int j2) {
        int cal = prefix[i2][j2];
        if (i1 > 0)
            cal -= prefix[i1 - 1][j2];
        if (j1 > 0)
            cal -= prefix[i2][j1 - 1];
        if (i1 > 0 && j1 > 0)
            cal += prefix[i1 - 1][j1 - 1];
        return cal;
    }
}