import java.io.*;
import java.util.*;

public class c {
    static int mod = 1000000007;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int[][] board = new int[n + 2][m + 2];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < m; j++) {
                board[i + 1][j + 1] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        Map<Integer, ArrayList<int[]>> map = new HashMap<>();
        ArrayList<Integer> indices = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!map.containsKey(board[i][j])) {
                    map.put(board[i][j], new ArrayList<>());
                    indices.add(board[i][j]);
                }
                map.get(board[i][j]).add(new int[] { i, j });
            }
        }
        Collections.sort(indices);
        int inf = 1000000000;
        int[] dx = new int[] { 1, 0, -1, 0 };
        int[] dy = new int[] { 0, 1, 0, -1 };
        Arrays.fill(board[0], inf);
        Arrays.fill(board[n + 1], inf);
        for (int i = 0; i < board.length; i++) {
            board[i][0] = board[i][m + 1] = inf;
        }
        boolean[][] end = new boolean[n + 2][m + 2];
        boolean[][] start = new boolean[n + 2][m + 2];
        int[][][] dp = new int[n + 2][m + 2][4];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                end[i][j] = true;
                start[i][j] = true;
                for (int k = 0; k < dx.length; k++) {
                    if (board[i + dx[k]][j + dy[k]] == board[i][j] + 1)
                        end[i][j] = false;
                    if (board[i + dx[k]][j + dy[k]] == board[i][j] - 1)
                        start[i][j] = false;
                }
                if (start[i][j])
                    dp[i][j][0] = 1;
            }
        }
        for (int indice : indices) {
            for (int[] index : map.get(indice)) {
                for (int k = 0; k < dx.length; k++) {
                    if (board[index[0] + dx[k]][index[1] + dy[k]] == board[index[0]][index[1]] - 1) {
                        for (int l = 0; l < 4; l++) {
                            int ind = l == 3 ? 3 : l + 1;
                            dp[index[0]][index[1]][ind] = modulo(
                                    dp[index[0]][index[1]][ind] + dp[index[0] + dx[k]][index[1] + dy[k]][l]);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (end[i][j])
                    ans = modulo(ans + dp[i][j][3]);
            }
        }
        System.out.println(ans);

        in.close();
    }

    public static int modulo(int i) {
        if (i >= mod)
            i -= mod;
        return i;
    }
}