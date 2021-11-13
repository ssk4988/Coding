/*
ID: ssk49881
LANG: JAVA
TASK: prob4
*/

import java.io.*;
import java.util.*;

public class prob4 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int numCases = Integer.parseInt(in.readLine());
        for (int count = 0; count < numCases; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            long[][] canals = new long[m][n];
            for (int i = 0; i < m; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < n; j++) {
                    canals[i][j] = Integer.parseInt(tokenizer.nextToken()) * 2097152;
                }
            }
            long minTime = -1;
            LinkedList<Path> queue = new LinkedList<>();
            queue.addFirst(new Path(0, 0, canals[0][0], 0));
            while (!queue.isEmpty()) {
                Path path = queue.pollFirst();
                if (path.x == m - 1 && path.y == n - 1) {

                    if (minTime < 0 || path.time < minTime) {
                        minTime = path.time;
                    }

                }
                if (path.y < n - 1) {
                    Path c = new Path(path.x, path.y + 1, (path.currentHeight + canals[path.x][path.y + 1]) / 2,
                            path.time + Math.abs(canals[path.x][path.y + 1] - path.currentHeight) / 2);
                    queue.add(c);
                }
                if (path.x < m - 1) {
                    Path c = new Path(path.x + 1, path.y, (path.currentHeight + canals[path.x + 1][path.y]) / 2,
                            path.time + Math.abs(canals[path.x + 1][path.y] - path.currentHeight) / 2);
                    queue.add(c);
                }
            }
            System.out.printf("Canal %d: %.3f\n", (count + 1), (float) minTime / 2097152);
        }

        in.close();
        out.close();
    }

    public static class Path {
        int x;
        int y;
        long currentHeight;
        long time;

        public Path(int x, int y, long currentHeight, long time) {
            this.x = x;
            this.y = y;
            this.currentHeight = currentHeight;
            this.time = time;
        }
    }
}