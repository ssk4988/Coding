import java.io.*;
import java.util.*;

public class p008 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        piece[] p = new piece[n];
        Map<Integer, piece> map = new HashMap<>();
        piece corner1 = null;
        int zcnt = 0;
        boolean works = true;
        int[] dx = new int[] { -1, 0, 1, 0 };
        int[] dy = new int[] { 0, -1, 0, 1 };
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] edges = new int[4];
            for (int j = 0; j < 4; j++) {
                edges[j] = Integer.parseInt(tokenizer.nextToken());
            }
            p[i] = new piece(i + 1, edges);
            for (int j = 0; j < 4; j++) {
                if (p[i].edges[j] == 0)
                    continue;
                piece p1 = map.get(p[i].edges[j]);
                if (p1 == null) {
                    map.put(p[i].edges[j], p[i]);
                } else {
                    p[i].pedges[j] = p1;
                    for (int k = 0; k < 4; k++) {
                        if (p1.edges[k] == p[i].edges[j]) {
                            p1.pedges[k] = p[i];
                        }
                    }
                }
            }
            if (p[i].zeros > zcnt) {
                corner1 = p[i];
                zcnt = p[i].zeros;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                if ((p[i].edges[j] != 0 && p[i].pedges[j] == null)||(p[i].edges[j] == 0 && p[i].pedges[j] != null)) {
                    works = false;
                }
            }
        }
        if (corner1 == null || zcnt < 2)
            works = false;
        int rot = 0;
        while (rot < 6) {
            if (corner1.edges[rot % 4] == 0 && corner1.edges[(rot + 1) % 4] == 0) {
                break;
            }
            rot++;
        }
        if (rot == 6)
            works = false;
        else
            corner1.rotate(-rot);
        corner1.x = 0;
        corner1.y = 0;
        ArrayDeque<piece> queue = new ArrayDeque<>();
        queue.add(corner1);
        int[] rot2 = new int[] { 2, 3, 0, 1 };
        find: while (!queue.isEmpty() && works) {
            piece p1 = queue.poll();
            for (int i = 0; i < 4; i++) {
                if (p1.pedges[i] != null) {
                    int x = p1.x + dx[i];
                    int y = p1.y + dy[i];
                    if (p1.pedges[i].x == -1 && p1.pedges[i].y == -1) {
                        p1.pedges[i].x = x;
                        p1.pedges[i].y = y;
                        queue.add(p1.pedges[i]);
                    } else if (p1.pedges[i].x == x && p1.pedges[i].y == y) {
                    } else {
                        works = false;
                        break find;
                    }
                    for (int j = 0; j < 4; j++) {
                        if (p1.pedges[i].edges[j] == p1.edges[i]) {
                            p1.pedges[i].rotate(rot2[i] - j);
                            break;
                        }
                    }
                    if (p1.pedges[i].pedges[rot2[i]] != p1) {
                        works = false;
                        break find;
                    }
                }
            }
        }
        int maxX = 0;
        int maxY = 0;
        o1: for (int i = 0; i < p.length && works; i++) {
            maxX = Math.max(p[i].x, maxX);
            maxY = Math.max(p[i].y, maxY);
            for (int j = 0; j < 4; j++) {
                if (p[i].pedges[j] != null) {
                    if (p[i].pedges[j].pedges[rot2[j]] != p[i]) {
                        works = false;
                        break o1;
                    }
                }
            }
        }
        if((maxX + 1) * (maxY + 1) != n) works = false;
        piece[][] board = new piece[maxX + 1][maxY + 1];
        o2: for (int i = 0; i < n && works; i++) {
            if (p[i].x < 0 || p[i].x > maxX || p[i].y < 0 || p[i].y > maxY || board[p[i].x][p[i].y] != null) {
                works = false;
                break o2;
            }
            board[p[i].x][p[i].y] = p[i];
        }
        o3: for (int i = 0; i < board.length && works; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j] == null) {
                    works = false;
                    break o3;
                }
                for (int k = 0; k < 4; k++) {
                    if (board[i][j].pedges[k] != null && board[i + dx[k]][j + dy[k]] != board[i][j].pedges[k]) {
                        works = false;
                        break o3;
                    }
                }
            }
        }
        o4: for (int i = 0; i < board.length && works; i++) {
            if (board[i][0].pedges[1] != null || board[i][board[i].length - 1].pedges[3] != null) {
                works = false;
                break o4;
            }
        }
        o5: for (int i = 0; i < board[0].length && works; i++) {
            if (board[0][i].pedges[0] != null || board[board.length - 1][i].pedges[2] != null) {
                works = false;
                break o5;
            }
        }
        o6: for (int i = 0; i < board.length && works; i++) {
            for (int j = 0; j < board[i].length; j++) {
                for (int k = 0; k < 4; k++) {
                    if (i + dx[k] >= 0 && i + dx[k] < board.length && j + dy[k] >= 0 && j + dy[k] < board[i].length
                            && (board[i][j].pedges[k] == null
                                    || board[i][j].pedges[k].pedges[rot2[k]] != board[i][j])) {
                        {
                            works = false;
                            break o6;
                        }
                    }
                }
            }
        }
        if (works) {
            StringBuilder b = new StringBuilder();
            b.append(board.length + " " + board[0].length + "\n");
            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[i].length; j++) {
                    b.append(board[i][j].id + (j + 1 < board[i].length ? " " : "\n"));
                }
            }
            System.out.print(b);
        } else {
            System.out.println("impossible");
        }
        in.close();
    }

    public static class piece {
        int[] edges;
        piece[] pedges = new piece[4];
        int id;
        int x = -1;
        int y = -1;
        int zeros = 0;

        public piece(int id, int[] edges) {
            this.edges = edges;
            this.id = id;
            for (int i = 0; i < edges.length; i++) {
                if (edges[i] == 0)
                    zeros++;
            }
        }

        public void rotate(int num) {
            int[] e2 = new int[4];
            piece[] p2 = new piece[4];
            for (int i = 0; i < 4; i++) {
                p2[(i + num + 4) % 4] = pedges[i];
                e2[(i + num + 4) % 4] = edges[i];
            }
            edges = e2;
            pedges = p2;
        }
    }
}