import java.io.*;
import java.util.*;

public class l {
    static int[] dx = new int[] { 1, 0, -1, 0 };
    static int[] dy = new int[] { 0, 1, 0, -1 };
    static int[] kx = new int[] { 1, 2, 2, 1, -1, -2, -2, -1 };
    static int[] ky = new int[] { 2, 1, -1, -2, -2, -1, 1, 2 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int r = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        node[][] board = new node[r][c];
        int[] rc = new int[2];
        for (int i = 0; i < r; i++) {
            String s = in.readLine();
            for (int j = 0; j < c; j++) {
                board[i][j] = new node(i, j);
                if (s.charAt(j) == 'R') {
                    rc = new int[] { i, j };
                }
                if (s.charAt(j) == 'K') {
                    board[i][j].knight = true;
                }
                if (s.charAt(j) == 'T') {
                    board[i][j].target = true;
                }
            }
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (board[i][j].knight) {
                    for (int k = 0; k < kx.length; k++) {
                        if (i + kx[k] >= 0 && i + kx[k] < r && j + ky[k] >= 0 && j + ky[k] < c) {
                            board[i + kx[k]][j + ky[k]].protection++;
                        }
                    }
                }
            }
        }

        ArrayDeque<node> q = new ArrayDeque<>();
        q.add(board[rc[0]][rc[1]]);
        boolean answer = false;
        while (!q.isEmpty()) {
            node n = q.poll();
            if (n.captured)
                continue;
            n.captured = true;

            if (n.target) {
                answer = true;
                break;
            }
            if (n.knight) {
                n.knight = false;
                for (int k = 0; k < kx.length; k++) {
                    if (n.r + kx[k] >= 0 && n.r + kx[k] < r && n.c + ky[k] >= 0 && n.c + ky[k] < c) {
                        board[n.r + kx[k]][n.c + ky[k]].protection--;
                        if (board[n.r + kx[k]][n.c + ky[k]].protection <= 0
                                && !board[n.r + kx[k]][n.c + ky[k]].captured) {
                            protloop: for (int k1 = 0; k1 < dx.length; k1++) {
                                int i1 = n.r + kx[k], i2 = n.c + ky[k];
                                while (i1 >= 0 && i1 < r && i2 >= 0 && i2 < c) {
                                    if (board[i1][i2].captured) {
                                        q.add(board[n.r + kx[k]][n.c + ky[k]]);
                                        break protloop;
                                    }
                                    if (board[i1][i2].knight)
                                        break;
                                    i1 += dx[k1];
                                    i2 += dy[k1];
                                }
                            }
                        }
                    }
                }
            }
            for (int k = 0; k < dx.length; k++) {
                int i1 = n.r, i2 = n.c;
                while (i1 >= 0 && i1 < r && i2 >= 0 && i2 < c) {
                    if (!board[i1][i2].captured && board[i1][i2].protection <= 0) {
                        q.add(board[i1][i2]);
                    }
                    if (board[i1][i2].knight)
                        break;
                    i1 += dx[k];
                    i2 += dy[k];
                }
            }
        }
        System.out.println(answer ? "yes" : "no");
    }

    static class node {
        int r;
        int c;
        boolean knight = false;
        boolean captured = false;
        int protection = 0;
        boolean target = false;

        public node(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
}
