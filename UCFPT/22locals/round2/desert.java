import java.io.*;
import java.util.*;

public class desert {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int o = Integer.parseInt(in.readLine());
        int[][] c = new int[o][2];
        HashSet<Integer>[] cp = new HashSet[o];
        int[] cpt = new int[o];
        long[][] dp = new long[o][o];
        for (int i = 0; i < o; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            c[i][0] = Integer.parseInt(tokenizer.nextToken());
            c[i][1] = Integer.parseInt(tokenizer.nextToken());
            cp[i] = new HashSet<>();
            cp[i].add(i);
            cpt[i] = i;
        }

        ArrayList<edge> e = new ArrayList<>();
        for (int i = 0; i < o; i++) {
            for (int j = 0; j < o; j++) {
                long dist = ((long) c[i][0] - c[j][0]) * ((long) c[i][0] - c[j][0])
                        + ((long) c[i][1] - c[j][1]) * ((long) c[i][1] - c[j][1]);
                e.add(new edge(i, j, dist));
            }
        }
        Collections.sort(e);
        for (edge e1 : e) {
            if (cpt[e1.i] == cpt[e1.j]) {
                continue;
            }
            int c1 = cp[cpt[e1.i]].size() >= cp[cpt[e1.j]].size() ? cpt[e1.i] : cpt[e1.j];
            int c2 = cp[cpt[e1.i]].size() >= cp[cpt[e1.j]].size() ? cpt[e1.j] : cpt[e1.i];
            // c1 more size
            for (int i : cp[c1]) {
                for (int j : cp[c2]) {
                    dp[i][j] = dp[j][i] = e1.d;
                }
            }
            for (int j : cp[c2]) {
                cp[c1].add(j);
                cpt[j] = c1;
            }
        }
        int q = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for (int i = 0; i < q; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            out.append(Math.sqrt(dp[a][b]) + "\n");
        }
        System.out.print(out);
    }

    public static class edge implements Comparable<edge> {
        int i;
        int j;
        long d = 0;

        public edge(int i, int j, long d) {
            this.i = i;
            this.j = j;
            this.d = d;
        }

        @Override
        public int compareTo(desert.edge o) {
            // MAKE SURE THSI DOESNT AFFECT ELEMENT EQUALITY
            if (d < o.d)
                return -1;
            if (d > o.d)
                return 1;
            return 0;
        }
    }
}