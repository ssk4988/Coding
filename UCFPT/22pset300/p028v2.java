import java.io.*;
import java.util.*;

public class p028v2 {
    public static int maxN = 2010;
    public static char[][] board = new char[maxN][maxN];
    public static int[][] prefix = new int[maxN][maxN];
    public static boolean[] composite = new boolean[maxN];
    public static TreeSet<Integer> primes = new TreeSet<>();
    public static int n;
    public static int minX, minY, maxX, maxY;
    public static int infinity = 1000000;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(in.readLine());
        composite[0] = composite[1] = true;
        for (int i = 2; i < composite.length; i++) {
            if (composite[i])
                continue;
            primes.add(i);
            for (int j = 2 * i; j < composite.length; j += i) {
                composite[j] = true;
            }
        }
        for (int i = 1; i <= n; i++) {
            String s = in.readLine();
            for (int j = 1; j <= n; j++) {
                board[i][j] = s.charAt(j - 1);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = (board[i][j] == '-' ? 1 : 0) + prefix[i - 1][j] + prefix[i][j - 1]
                        - prefix[i - 1][j - 1];
            }
        }
        compute();
        boolean elim = eliminate();
        boolean ruby = prefix[n][n] % 2 == 1 ? elim : maxY > 0;
        System.out.println(ruby ? "RUBY" : "DIA");

        in.close();
    }

    public static boolean eliminate() {
        if (maxX == 0)
            return true;
        for (int x1 = minX; x1 <= minX + 1; x1++) {
            for (int x2 = maxX - 1; x2 <= maxX; x2++) {
                for (int y1 = minX; y1 <= minX + 1; y1++) {
                    for (int y2 = maxY - 1; y2 <= maxY; y2++) {
                        if (x2 - x1 != y2 - y1 || x1 > x2)
                            continue;
                        if (calc(x1, y1, x2, y2) != (x2 - x1 + 1) * (x2 - x1 + 1))
                            continue;
                        if (!primes.contains(x2 - x1 + 1) || x2 - x1 == 1)
                            continue;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    public static void compute() {
        minX = minY = infinity;
        maxX = maxY = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (calc(i, j, i + 1, j + 1) == 4) {
                    minX = Math.min(minX, i);
                    maxX = Math.max(maxX, i + 1);
                    minY = Math.min(minY, j);
                    maxY = Math.max(maxY, j + 1);
                }
            }
        }
    }

    public static int calc(int i1, int j1, int i2, int j2) {
        return prefix[i2][j2] - prefix[i1 - 1][j2] - prefix[i2][j1 - 1] + prefix[i1 - 1][j1 - 1];
    }
}