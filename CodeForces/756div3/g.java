/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            in.readLine();
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            int[][] board = new int[n][m];
            for (int i = 0; i < n; i++) {
                String s = in.readLine();
                for (int j = 0; j < m; j++) {
                    board[i][j] = s.charAt(j) - '0';
                }
            }
            HashMap<Integer, TreeSet<Integer>>[] grid = new HashMap[2];
            grid[0] = new HashMap<>();
            grid[1] = new HashMap<>();
            TreeSet<Integer>[] columns = new TreeSet[2];
            columns[0] = new TreeSet<>();
            columns[1] = new TreeSet<>();
            // white (i+j) even, black (i+j) odd
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (board[i][j] == 1) {
                        int type = (i + j) % 2;
                        int col = (i + type) / 2 + j / 2;
                        columns[type].add(col);
                        add(grid[type], col, i);
                    }
                }
            }
            int answer = 0;
            for (int t = 0; t < 2; t++) {
                HashMap<Integer, TreeSet<Integer>> map = grid[t];
                while (columns[t].size() > 0) {
                    int currCol = columns[t].pollFirst();
                    while (map.get(currCol).size() > 0) {
                        int x = 0;
                        int y = currCol;
                        while (x < n) {
                            if (!map.containsKey(y) || map.get(y).contains(x)) {
                                remove(map, y, x);
                            }
                            Integer next = (!map.containsKey(y)) ? null : map.get(y).higher(x);
                            if (next == null) {
                                y++;
                            }
                            x++;
                        }
                        answer++;
                    }
                }
            }
            System.out.println(answer);
        }

        in.close();
        out.close();
    }

    public static void add(HashMap<Integer, TreeSet<Integer>> m, int key, int val) {
        if (!m.containsKey(key))
            m.put(key, new TreeSet<>());
        m.get(key).add(val);
    }

    public static void remove(HashMap<Integer, TreeSet<Integer>> m, int key, int val) {
        if (m.containsKey(key))
            m.get(key).remove(val);
    }
}