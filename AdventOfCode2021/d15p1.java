import java.io.*;
import java.util.*;

public class d15p1 {
    public static int[] dx = { 1, 0, -1, 0 };
    public static int[] dy = { 0, 1, 0, -1 };
    public static boolean p1 = false;
    public static int tile = p1 ? 1 : 5;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d15p1.in"));
        long start = System.currentTimeMillis();
        String line;
        ArrayList<String> input = new ArrayList<>();
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        int m = input.size();
        int n = input.get(0).length();
        sq[][] board = new sq[m * tile][n * tile];
        for (int k = 0; k < tile; k++) {
            for (int l = 0; l < tile; l++) {
                for (int i = 0; i < m; i++) {
                    String s = input.get(i);
                    for (int j = 0; j < n; j++) {
                        board[m * k + i][n * l + j] = new sq(m * k + i, n * l + j, (s.charAt(j) - '1' + k + l) % 9 + 1);
                    }
                }
            }
        }

        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                board[i][j].getC(board, m, n);
            }
        }
        LinkedList<sq> list = new LinkedList<>();
        PriorityQueue<sq> q = new PriorityQueue<>(new comp());
        board[0][0].dist = 0;
        for (int i = board.length - 1; i >= 0; i--) {
            for (int j = board[i].length - 1; j >= 0; j--) {
                list.addFirst(board[i][j]);
                q.add(board[i][j]);
            }
        }

        for (int k = 0; k < board.length * board[0].length - 1; k++) {
            if (k % 10000 == 0)
                System.out.println(k + " out of " + (board.length * board[0].length - 1) + " time: "
                        + (System.currentTimeMillis() - start) + " finish: "
                        + ((System.currentTimeMillis() - start) * (board.length * board[0].length - 1) / (k + 1)));
            sq minsq = null;
            while (minsq == null || minsq.inSet) {
                minsq = q.poll();
            }

            minsq.inSet = true;
            // System.out.println(minsq.dist);
            for (sq c : minsq.neighbors) {
                if (!c.inSet && minsq.dist != Integer.MAX_VALUE && c.dist > minsq.dist + c.val) {
                    q.remove(c);
                    c.dist = minsq.dist + c.val;
                    q.add(c);
                }
            }
            if (minsq.x == board.length - 1 && minsq.y == board[0].length - 1) {
                System.out.println("k: " + k);
                break;
            }
        }
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                // System.out.print(board[i][j].dist + " ");
            }
            // System.out.println();
        }
        System.out.println(
                board[board.length - 1][board[0].length - 1].dist + " " + (System.currentTimeMillis() - start));
        in.close();
    }

    public static class comp implements Comparator<sq> {
        @Override
        public int compare(sq o1, sq o2) {
            if (o1.dist == o2.dist) {
                if (o1.x == o2.x) {
                    return o1.y - o2.y;
                }
                return o1.x - o2.x;
            }
            return o1.dist - o2.dist;
        }
    }

    public static class sq implements Comparable<sq> {
        int x = 0;
        int y = 0;
        int val = 0;
        int dist = Integer.MAX_VALUE;
        boolean inSet = false;
        ArrayList<sq> neighbors = new ArrayList<>();

        public sq(int x, int y, int val) {
            this.x = x;
            this.y = y;
            this.val = val;
        }

        @Override
        public int compareTo(sq o) {
            return this.dist - o.dist;
        }

        public void getC(sq[][] board, int m, int n) {
            if (this.val == 0)
                return;
            for (int i = 0; i < dx.length; i++) {
                int newx = x + dx[i];
                int newy = y + dy[i];
                if (newx < board.length && newx >= 0 && newy < board[0].length && newy >= 0) {
                    neighbors.add(board[newx][newy]);
                }
            }
        }
    }
}