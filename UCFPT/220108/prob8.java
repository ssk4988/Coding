import java.io.*;
import java.util.*;

public class prob8 {
    public static boolean solved = false;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;
        while (!(line = in.readLine()).equals("0")) {
            int n = Integer.parseInt(line);
            int[][] board = new int[n][n];
            for (int i = 0; i < n; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < n; j++) {
                    board[i][j] = Integer.parseInt(tokenizer.nextToken());
                }
            }
            boolean works = true;
            for (int i = 0; i < n; i++) {
                Set<Integer> row = new HashSet<>();
                Set<Integer> col = new HashSet<>();
                for (int j = 0; j < n; j++) {
                    if (row.contains(board[i][j]) || col.contains(board[j][i])) {
                        works = false;
                    }
                    if (board[i][j] > 0) {
                        row.add(board[i][j]);
                    }
                    if (board[j][i] > 0) {
                        col.add(board[j][i]);
                    }
                }
            }
            int sn = (n == 1 ? 1 : (n == 4 ? 2 : (n == 9 ? 3 : 4)));
            for (int i = 0; i < sn; i++) {
                for (int j = 0; j < sn; j++) {
                    Set<Integer> s = new HashSet<>();
                    for (int k = 0; k < sn; k++) {
                        for (int l = 0; l < sn; l++) {
                            if (s.contains(board[i * sn + k][j * sn + l])) {
                                works = false;
                            }
                            if (board[i * sn + k][j * sn + l] > 0) {
                                s.add(board[i * sn + k][j * sn + l]);
                            }
                        }
                    }
                }
            }
            if (!works) {
                System.out.println("ILLEGAL BOARD");
                continue;
            }
            group[][] groups = new group[3][n]; // row, col, sq
            for (int i = 0; i < groups.length; i++) {
                for (int j = 0; j < groups[i].length; j++) {
                    groups[i][j] = new group(i, j, n);
                }
            }
            square[][] sq = new square[n][n];
            Set<square> left = new HashSet<>();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sq[i][j] = new square(i, j, board[i][j], sn, groups);
                    groups[0][i].add(sq[i][j]);
                    groups[1][j].add(sq[i][j]);
                    sq[i][j].sq.add(sq[i][j]);
                    if (!sq[i][j].fixed) {
                        left.add(sq[i][j]);
                    }
                }
            }
            solved = false;
            dfs(sq, left);
        }

        in.close();
        out.close();
    }

    public static void dfs(square[][] sq, Set<square> left) {
        if (solved)
            return;
        square curr = choose(left);
        if (curr == null) {
            StringBuilder b = new StringBuilder();
            for (int i = 0; i < sq.length; i++) {
                for (int j = 0; j < sq[i].length; j++) {
                    b.append(sq[i][j].val + (j + 1 < sq[i].length ? " " : "\n"));
                }
            }
            System.out.print(b);
            return;
        }
        Set<Integer> ns = new HashSet<>();
        ns.addAll(curr.row.possibilities);
        ns.retainAll(curr.col.possibilities);
        ns.retainAll(curr.sq.possibilities);
        for (int p : ns) {
            if (solved)
                return;
            curr.val = p;
            curr.used = true;
            curr.row.possibilities.remove(p);
            curr.col.possibilities.remove(p);
            curr.sq.possibilities.remove(p);
            left.remove(curr);
            dfs(sq, left);
            left.add(curr);
            curr.sq.possibilities.add(p);
            curr.col.possibilities.add(p);
            curr.row.possibilities.add(p);
            curr.used = false;
            curr.val = 0;
        }
    }

    public static square choose(Set<square> left) {
        square min = null;
        for (square sq : left) {
            if (min == null || (sq.row.possibilities.size() - 1) * (sq.col.possibilities.size() - 1)
                    * (sq.sq.possibilities.size() - 1) < (min.row.possibilities.size() - 1)
                            * (min.col.possibilities.size() - 1)
                            * (min.sq.possibilities.size() - 1)) {
                min = sq;
            }
        }
        return min;
    }

    public static class group {
        int type;
        int id;
        Set<Integer> possibilities = new HashSet<>();
        Set<square> children = new HashSet<>();

        public group(int type, int id, int n) {
            this.type = type;
            this.id = id;
            for (int i = 0; i < n; i++) {
                possibilities.add(i + 1);
            }
        }

        public void add(square child) {
            children.add(child);
            possibilities.remove(child.val);
        }

        public void remove(square child) {
            children.remove(child);
            possibilities.add(child.val);
        }
    }

    public static class square {
        int x;
        int y;
        group row;
        group col;
        group sq;
        int val;
        boolean used;
        boolean fixed;
        Set<Integer> possibilities = new HashSet<>();

        public square(int x, int y, int val, int sn, group[][] groups) {
            this.x = x;
            this.y = y;
            this.val = val;
            used = val != 0;
            row = groups[0][x];
            col = groups[1][y];
            sq = groups[2][x / sn * sn + y / sn];
            fixed = used;
            if (!fixed) {
                for (int i = 0; i < sn * sn; i++) {
                    possibilities.add(i + 1);
                }
            }
        }
    }
}