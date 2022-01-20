import java.io.*;
import java.util.*;

public class d {
    public static int[] dx = { 1, 0, -1, 0 };
    public static int[] dy = { 0, 1, 0, -1 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            sq[][] b = new sq[2 * n][2 * n];
            for (int i = 0; i < b.length; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < b[i].length; j++) {
                    b[i][j] = new sq(i, j, Integer.parseInt(tokenizer.nextToken()));
                }
            }
            for (int i = 0; i < b.length; i++) {
                for (int j = 0; j < b[i].length; j++) {
                    for (int k = 0; k < dx.length; k++) {
                        b[i][j].ns[k] = b[(b.length + i + dx[k]) % b.length][(b.length + j + dy[k]) % b[i].length];
                    }
                }
            }
            long cost = 0;
            for (int i = n; i < b.length; i++) {
                for (int j = n; j < b[i].length; j++) {
                    cost += b[i][j].cost;
                    b[i][j].cost = 0;
                }
            }
            long min = Math.min(Math.min(Math.min(b[0][n].cost, b[0][2*n-1].cost), Math.min(b[n-1][n].cost, b[n-1][2*n-1].cost)), Math.min(Math.min(b[n][0].cost, b[n][n-1].cost), Math.min(b[2*n-1][0].cost,b[2*n-1][n-1].cost)));
            System.out.println(min + cost);
        }

        in.close();
        out.close();
    }

    public static class comp implements Comparator<sq> {
        @Override
        public int compare(d.sq o1, d.sq o2) {
            if (o1.dist < o2.dist)
                return -1;
            if (o1.dist > o2.dist)
                return 1;
            return 0;
        }
    }

    public static class sq {
        int r;
        int c;
        int cost;
        sq[] ns = new sq[4];
        boolean connected = false;
        long dist = Long.MAX_VALUE;

        public sq(int r, int c, int cost) {
            this.r = r;
            this.c = c;
            this.cost = cost;
        }
    }
}