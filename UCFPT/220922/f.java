import java.util.*;
public class f {
    static char[][] board;
    static char[][] result;
    static int[][] grid;
    static int n;

    static char getBoard(int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= n) {
            return 0;
        }
        return board[i][j];
    }

    static char getRes(int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= n) {
            return 0;
        }
        return result[i][j];
    }
    static boolean setBoard(int i, int j, char ch) {
        if (i < 0 || j < 0 || i >= n || j >= n) {
            return false;
        }
        if (board[i][j] == ch) {
            return false;
        }
        board[i][j] = ch;
        return true;
    }

    static boolean fillStuff(int i, int j) {
        if (grid[i][j] == -1) return false; // did nothing

        int[][] sur = new int[2][2];
        char c;
        c = getBoard(i - 1, j - 1); sur[0][0] = c == 0 ? -2 : c == '\\' ? 1 : c == '/' ? -1 : 0;
        c = getBoard(i + 0, j - 1); sur[1][0] = c == 0 ? -2 : c == '/' ? 1 : c == '\\' ? -1 : 0;
        c = getBoard(i - 1, j + 0); sur[0][1] = c == 0 ? -2 : c == '/' ? 1 : c == '\\' ? -1 : 0;
        c = getBoard(i + 0, j + 0); sur[1][1] = c == 0 ? -2 : c == '\\' ? 1 : c == '/' ? -1 : 0;

        int ins = 0, zeros = 0, outs = 0;
        for (int[] arr : sur) {
            for (int v : arr) {
                if (v == 0) {
                    zeros++;
                }
                if (v == -1) {
                    outs++;
                }
                if (v == 1) {
                    ins++;
                }
            }
        }
        int total = ins + zeros + outs;

        int x = grid[i][j];
        if (zeros + ins == x) {
            for (int[] arr : sur) {
                for (int ii = 0; ii < 2; ++ii) {
                    if (arr[ii] == 0) arr[ii] = 1;
                }
            }
        }
        if (zeros + outs == total - x) {
            for (int[] arr : sur) {
                for (int ii = 0; ii < 2; ++ii) {
                    if (arr[ii] == 0) arr[ii] = -1;
                }
            }
        }

        boolean changes = false;
        if (sur[0][0] == 1) {
            changes = changes || setBoard(i - 1, j - 1, '\\');
        }
        else if (sur[0][0] == -1) {
            changes = changes || setBoard(i - 1, j - 1, '/');
        }

        if (sur[1][0] == 1) {
            changes = changes || setBoard(i + 0, j - 1, '/');
        }
        else if (sur[1][0] == -1) {
            changes = changes || setBoard(i + 0, j - 1, '\\');
        }

        if (sur[0][1] == 1) {
            changes = changes || setBoard(i - 1, j + 0, '/');
        }
        else if (sur[0][1] == -1) {
            changes = changes || setBoard(i - 1, j + 0, '\\');
        }

        if (sur[1][1] == 1) {
            changes = changes || setBoard(i + 0, j + 0, '\\');
        }
        else if (sur[1][1] == -1) {
            changes = changes || setBoard(i + 0, j + 0, '/');
        }

        return changes;
    }
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        n = scan.nextInt();
        scan.nextLine();
        grid = new int[n + 1][n + 1];
        board = new char[n][n];
        for (char[] i : board) Arrays.fill(i, ' ');
        for (int i = 0; i <= n; ++i) {
            char[] line = scan.nextLine().toCharArray();
            for (int j = 0; j <= n; ++j) {
                grid[i][j] = line[j] == '.' ? -1 : (line[j] - '0');
            }
        }
        while (true) {
            boolean didsmth = false;
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= n; ++j) {
                    didsmth = didsmth || fillStuff(i, j);
                }
            }
            if (!didsmth) break;
        }

        // minor opt, not sure if necessary:
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                char[][] exp = {{'/', '\\'}, {'\\', '/'}};
                int count = 0;
                int countEmpty = 0;
                for (int ii = 0; ii < 2; ++ii) {
                    for (int jj = 0; jj < 2; ++jj) {
                        if (board[i + ii][j + jj] == exp[ii][jj]) {
                            count++;
                        }
                        else if (board[i + ii][j + jj] == ' ') {
                            countEmpty++;
                        }
                    }
                }
                if (count == 3 && countEmpty == 1) {
                    for (int ii = 0; ii < 2; ++ii) {
                        for (int jj = 0; jj < 2; ++jj) {
                            if (board[i + ii][j + jj] == ' ') {
                                board[i + ii][j + jj] = exp[1 - ii][jj];
                                break;
                            }
                        }
                    }
                }
            }
        }

        // backtracking:

        result = new char[n][n];
        for (var i : result) {
            Arrays.fill(i, ' ');
        }
        boolean r = go(0, 0);
        if (!r) {
            throw new Error("lmao");
        }
        for (var i : result) {
            System.out.println(String.valueOf(i));
        }
    }

    static class point { int i, j; point parent;
        point(int i, int j, point parent) {
            this.i = i;this.j = j;
            this.parent = parent;
        }
        @Override
        public int hashCode() {
            final int prime = 31;
            int result = 1;
            result = prime * result + i;
            result = prime * result + j;
            return result;
        }
        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            if (getClass() != obj.getClass())
                return false;
            point other = (point) obj;
            if (i != other.i)
                return false;
            if (j != other.j)
                return false;
            return true;
        }
        
    }

    static boolean verify() {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                int[][] sur = new int[2][2];
                char c;
                c = getRes(i - 1, j - 1); sur[0][0] = c == 0 ? -2 : c == '\\' ? 1 : c == '/' ? -1 : 0;
                c = getRes(i + 0, j - 1); sur[1][0] = c == 0 ? -2 : c == '/' ? 1 : c == '\\' ? -1 : 0;
                c = getRes(i - 1, j + 0); sur[0][1] = c == 0 ? -2 : c == '/' ? 1 : c == '\\' ? -1 : 0;
                c = getRes(i + 0, j + 0); sur[1][1] = c == 0 ? -2 : c == '\\' ? 1 : c == '/' ? -1 : 0;

                int ins = 0, zeros = 0, outs = 0;
                for (int[] arr : sur) {
                    for (int v : arr) {
                        if (v == 0) {
                            zeros++;
                        }
                        if (v == -1) {
                            outs++;
                        }
                        if (v == 1) {
                            ins++;
                        }
                    }
                }

                int x = grid[i][j];
                if (x == -1) continue;
                if (ins + zeros < x || ins > x) {
                    return false;
                }
            }
        }


        boolean[][] visited = new boolean[n + 1][n + 1];
        ArrayDeque<point> q = new ArrayDeque<>();
        for (int si = 0; si <= n; ++si) {
            for (int sj = 0; sj <= n; ++sj) {
                if (visited[si][sj]) continue;
                visited[si][sj] = true;
                q.add(new point(si, sj, null));
                while (!q.isEmpty()) {
                    point cur = q.poll();

                    int[] dis = {0, -1, -1, 0};
                    int[] djs = {0, -1, 0, -1};
                    char[] chs = {'\\', '\\', '/', '/'};
                    for (int index = 0; index < dis.length; ++index) {
                        int di = dis[index];
                        int dj = djs[index];
                        char ch = chs[index];
                        if (getRes(cur.i + di, cur.j + dj) == ch) {
                            point next = new point(cur.i + (2 * di + 1), cur.j + (2 * dj + 1), cur);
                            if (!next.equals(cur.parent)) {
                                if (visited[next.i][next.j]) {
                                    return false;
                                }
                                visited[next.i][next.j] = true;
                                q.add(next);
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    static boolean go(int i, int j) {
        if (!verify()) {
            return false;
        }

        if (i == n) {
            return true;
        }

        int ni, nj;
        if (j == n - 1) {
            ni = i + 1;
            nj = 0;
        }
        else {
            ni = i;
            nj = j + 1;
        }

        if (board[i][j] != ' ') {
            result[i][j] = board[i][j];
            boolean succ = go(ni, nj);
            if (succ) return true;
            result[i][j] = ' ';
            return false;
        }

        result[i][j] = '\\';
        if (go(ni, nj)) {
            return true;
        }

        result[i][j] = '/';
        if (go(ni, nj)) {
            return true;
        }

        result[i][j] = ' ';
        return false;
    }
}
