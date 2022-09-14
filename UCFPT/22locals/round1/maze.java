import java.io.*;
import java.util.*;

public class maze {
    public static int[] dy = new int[] { -1, 0, 1, 1, 1, 0, -1, -1 };
    public static int[] dx = new int[] { -1, -1, -1, 0, 1, 1, 1, 0 };
    public static int[] cost = new int[] { 1, 2, 3, 4, 5, 6, 7, 8 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int nr = Integer.parseInt(tokenizer.nextToken());
        int nc = Integer.parseInt(tokenizer.nextToken());
        int r = Integer.parseInt(tokenizer.nextToken()) - 1;
        int c = Integer.parseInt(tokenizer.nextToken()) - 1;
        int e = Integer.parseInt(tokenizer.nextToken());
        node[][] b = new node[nr][nc];
        for (int i = 0; i < nr; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < nc; j++) {
                int v = Integer.parseInt(tokenizer.nextToken());
                b[i][j] = new node(i, j, v);
            }
        }
        b[r][c].left = e;
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                for (int k = 0; k < 8; k++) {
                    if (i + dx[k] >= 0 && i + dx[k] < nr && j + dy[k] >= 0 && j + dy[k] < nc) {
                        b[i][j].ns[k] = b[i + dx[k]][j + dy[k]];
                    }
                }
            }
        }
        PriorityQueue<node> q = new PriorityQueue<>(new cp());
        q.add(b[r][c]);

        while (!q.isEmpty()) {
            node n = q.poll();
            if (n.v)
                continue;
            n.v = true;
            if (n.t > 0)
                continue;
            for (int i = 0; i < 8; i++) {
                if (n.ns[i] != null && !n.ns[i].v && n.left - cost[i] >= 0 && n.left - cost[i] > n.ns[i].left) {
                    n.ns[i].left = n.left - cost[i];
                    q.add(n.ns[i]);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                if (b[i][j].v) {
                    ans = Math.max(ans, b[i][j].t);
                }
            }
        }
        System.out.println(ans);
        in.close();
    }

    public static class cp implements Comparator<node> {
        @Override
        public int compare(maze.node o1, maze.node o2) {
            if (o2.left == o1.left) {
                if (o1.x == o2.x)
                    return o1.y - o2.y;
                return o1.x - o2.x;
            }
            return o2.left - o1.left;
        }
    }

    public static class node {
        int x;
        int y;
        int left = -1;
        int t = 0;
        boolean v = false;
        node[] ns = new node[8];

        public node(int x, int y, int t) {
            this.x = x;
            this.y = y;
            this.t = t;
        }
    }
}