import java.io.*;
import java.util.*;

public class e {
    public static int[] dx = { 1, 0, -1, 0 };
    public static int[] dy = { 0, 1, 0, -1 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int m = Integer.parseInt(tokenizer.nextToken());
        int n = Integer.parseInt(tokenizer.nextToken());
        sq[][] board = new sq[m][n];
        for (int i = 0; i < m; i++) {
            String s = in.readLine();
            for (int j = 0; j < n; j++) {
                board[i][j] = new sq(i, j, s.charAt(j) - '0');
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j].getC(board, m, n);

            }
        }
        ArrayDeque<sq> queue = new ArrayDeque<>();

        board[0][0].reach = 0;
        int max = Integer.MAX_VALUE;
        queue.add(board[0][0]);
        while (!queue.isEmpty()) {
            sq s = queue.poll();
            for (sq c : s.children) {
                if (c.val <= max && (c.reach == -1 || c.reach > s.reach + 1)) {
                    queue.add(c);
                }
                c.reach = c.reach == -1 ? s.reach + 1 : Math.min(c.reach, s.reach + 1);
                if (c.x == m - 1 && c.y == n - 1) {
                    max = c.reach;
                }
            }
        }
        System.out.println(board[m - 1][n - 1].reach);
        in.close();
    }

    public static class sq {
        int x = 0;
        int y = 0;
        int val = 0;
        int reach = -1;
        boolean solved = false;
        ArrayList<sq> children = new ArrayList<>();
        ArrayList<sq> parents = new ArrayList<>();

        public sq(int x, int y, int val) {
            this.x = x;
            this.y = y;
            this.val = val;
        }

        public void getC(sq[][] board, int m, int n) {
            if (this.val == 0)
                return;
            for (int i = 0; i < dx.length; i++) {
                int newx = x + dx[i] * val;
                int newy = y + dy[i] * val;
                if (newx < m && newx >= 0 && newy < n && newy >= 0) {
                    children.add(board[newx][newy]);
                    board[newx][newy].parents.add(this);
                }
            }
        }
    }
}