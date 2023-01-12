import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken()), m = Integer.parseInt(tokenizer.nextToken());
        int[][] grid = new int[n][m];
        int[][][] hpref = new int[2][n][m];
        for (int i = 0; i < n; i++) {
            String s = in.readLine();
            for (int j = 0; j < m; j++) {
                if (s.charAt(j) == '.') {
                    grid[i][j] = 0;
                } else if (s.charAt(j) == '#') {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = 1;
                }
                if (grid[i][j] == -1) {
                    hpref[0][i][j]++;
                }
                if (grid[i][j] == 1) {
                    hpref[1][i][j]++;
                }
                if (j > 0) {
                    for (int k = 0; k < 2; k++) {
                        hpref[k][i][j] += hpref[k][i][j - 1];
                    }
                }
            }
        }
        int ans = 0;
        for (int c1 = 0; c1 < m; c1++) {
            cols: for (int c2 = c1 + 2; c2 < m; c2++) {
                ArrayList<Integer>[] medcnt = new ArrayList[2];
                for (int i = 0; i < 2; i++) {
                    medcnt[i] = new ArrayList<>();
                }
                for (int i = 0; i < n; i++) {
                    int k = query(hpref, 1, i, c1 + 1, c2 - 1);
                    int k1 = query(hpref, 0, i, c1 + 1, c2 - 1);
                    if (k1 > 0)
                        continue;
                    if (k < 2) {
                        medcnt[k].add(i);
                        if (k == 0) {
                            medcnt[1].add(i);
                        }
                    }
                }
                // first sweep with no meds in cols
                int r1 = 0, r2 = 0;
                int[] num = { query(hpref, 0, r1, c1, c1) + query(hpref, 0, r2, c2, c2),
                        query(hpref, 1, r1, c1, c1) + query(hpref, 1, r1, c2, c2) };
                int[] point = { 0, 0 };
                while (r1 < n && r2 < n && medcnt[1].size() > 0) {
                    while (r2 < n && (num[0] > 0 || num[1] > 0)) {
                        for (int i = 0; i < 2; i++) {
                            num[i] -= query(hpref, i, r1, c1, c1) + query(hpref, i, r1, c2, c2);
                        }
                        r1++;
                        if (r1 > r2) {
                            r2++;
                            if (r2 >= n)
                                break;
                            for (int i = 0; i < 2; i++) {
                                num[i] += query(hpref, i, r1, c1, c1) + query(hpref, i, r1, c2, c2);
                            }
                        }
                    }
                    while (r2 < n && num[0] == 0 && num[1] == 0) {
                        while (point[0] < medcnt[1].size() && medcnt[1].get(point[0]) < r1 + 1) {
                            point[0]++;
                        }
                        while (point[1] + 1 < medcnt[1].size() && medcnt[1].get(point[1] + 1) <= r2 - 1) {
                            point[1]++;
                        }
                        if (point[0] <= point[1]) {
                            ans = Math.max(ans, c2 - c1 - 1 + (r2 - r1 + 1) * 2);
                        }
                        r2++;
                        if (r2 < n) {
                            for (int i = 0; i < 2; i++) {
                                num[i] += query(hpref, i, r2, c1, c1) + query(hpref, i, r2, c2, c2);
                            }
                        }
                    }
                }
                // 2nd sweep
                r1 = 0;
                r2 = 0;
                num[0] = query(hpref, 0, r1, c1, c1) + query(hpref, 0, r2, c2, c2);
                num[1] = query(hpref, 1, r1, c1, c1) + query(hpref, 1, r1, c2, c2);
                point[0] = point[1] = 0;
                while (r1 < n && r2 < n && medcnt[0].size() > 0) {
                    while (r2 < n && (num[0] > 0 || num[1] > 1)) {
                        for (int i = 0; i < 2; i++) {
                            num[i] -= query(hpref, i, r1, c1, c1) + query(hpref, i, r1, c2, c2);
                        }
                        r1++;
                        if (r1 > r2) {
                            r2++;
                            if (r2 >= n)
                                break;
                            for (int i = 0; i < 2; i++) {
                                num[i] += query(hpref, i, r1, c1, c1) + query(hpref, i, r1, c2, c2);
                            }
                        }
                    }
                    while (r2 < n && num[0] == 0 && num[1] <= 1) {
                        while (point[0] < medcnt[0].size() && medcnt[0].get(point[0]) < r1 + 1) {
                            point[0]++;
                        }
                        while (point[1] + 1 < medcnt[0].size() && medcnt[0].get(point[1] + 1) <= r2 - 1) {
                            point[1]++;
                        }
                        if (point[0] <= point[1]) {
                            ans = Math.max(ans, c2 - c1 - 1 + (r2 - r1 + 1) * 2);
                        }
                        r2++;
                        if (r2 < n) {
                            for (int i = 0; i < 2; i++) {
                                num[i] += query(hpref, i, r2, c1, c1) + query(hpref, i, r2, c2, c2);
                            }
                        }
                    }
                }
            }
        }
        System.out.println(ans);

        in.close();
    }

    static int query(int[][][] hpref, int type, int row, int c1, int c2) {
        int ans = hpref[type][row][c2];
        if (c1 > 0) {
            ans -= hpref[type][row][c1 - 1];
        }
        return ans;
    }
}