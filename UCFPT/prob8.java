import java.io.*;
import java.util.*;

public class prob8 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int numTimes = Integer.parseInt(in.readLine());
        for (int count = 0; count < numTimes; count++) {
            // if(count > 0) continue;
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            int sLen = Integer.parseInt(tokenizer.nextToken());
            Board b = new Board(m, n, sLen);
            for (int i = 0; i < m; i++) {
                String s = in.readLine();
                for (int j = 0; j < n; j++) {
                    char c = s.charAt(j);
                    int a = c == '.' ? -1 : (c == '#' ? -2 : (c == 'x' ? -3 : c - '0'));
                    b.board[i][j] = a;
                    if (a >= 0) {
                        b.coords[a] = i * n + j;
                    }
                }
                // System.out.println(Arrays.toString(b.board[i]));
            }
            // b.getChildren();
            for (Board c : b.children) {
                for (int i = 0; i < m; i++) {
                    // System.out.println(Arrays.toString(c.board[i]));
                }
            }
            Queue<Board> list = new LinkedList<Board>();
            ArrayList<String> seen = new ArrayList<>();
            list.add(b);
            int answer = -1;
            bfs: while (!list.isEmpty()) {
                Board p = list.poll();
                String ident = Arrays.toString(p.coords);
                int index = Collections.binarySearch(seen, Arrays.toString(p.coords));
                index = index < 0 ? -(index + 1) : index;
                seen.add(index, ident);
                p.getChildren();
                for (Board c : p.children) {
                    if (c.solved) {
                        answer = c.depth;
                        break bfs;
                    }
                    if (Collections.binarySearch(seen, Arrays.toString(c.coords)) >= 0) {
                        continue;
                    }
                    list.add(c);
                }
            }
            System.out.println("Game #" + (count + 1) + ": " + answer);
        }
        in.close();
        // out.close();
    }

    public static class Board {
        int m;
        int n;
        int[][] board;
        int[] coords;
        int sLen;
        int depth = 0;
        boolean solved = false;
        ArrayList<Board> parents = new ArrayList<>();
        ArrayList<Board> children = new ArrayList<>();

        public Board(int m, int n, int sLen) {
            this.m = m;
            this.n = n;
            this.sLen = sLen;
            board = new int[m][n];
            coords = new int[sLen];
        }

        public void getChildren() {
            int x = coords[0] / n;
            int y = coords[0] % n;
            ArrayList<Integer> newCoords = new ArrayList<>();
            // System.out.println(coords[0] + " " + x + " " + y + " " + board.length + " " +
            // board[0].length);

            if (x > 0
                    && ((board[x - 1][y] == sLen - 1 && sLen > 2) || board[x - 1][y] == -1 || board[x - 1][y] == -3)) {
                newCoords.add((x - 1) * n + y);
            }
            if (y > 0
                    && ((board[x][y - 1] == sLen - 1 && sLen > 2) || board[x][y - 1] == -1 || board[x][y - 1] == -3)) {
                newCoords.add((x) * n + y - 1);
            }
            if (x < m - 1
                    && ((board[x + 1][y] == sLen - 1 && sLen > 2) || board[x + 1][y] == -1 || board[x + 1][y] == -3)) {
                newCoords.add((x + 1) * n + y);
            }
            if (y < n - 1
                    && ((board[x][y + 1] == sLen - 1 && sLen > 2) || board[x][y + 1] == -1 || board[x][y + 1] == -3)) {
                newCoords.add((x) * n + y + 1);
            }
            for (int nC : newCoords) {
                int x2 = nC / n;
                int y2 = nC % n;

                Board c = new Board(m, n, sLen);
                for (int i = 0; i < m; i++) {
                    c.board[i] = board[i].clone();
                }
                c.solved = board[x2][y2] == -3;
                c.coords = coords.clone();
                c.depth = depth + 1;
                c.board[c.coords[sLen - 1] / n][c.coords[sLen - 1] % n] = -1;
                for (int i = sLen - 1; i > 0; i--) {
                    c.coords[i] = c.coords[i - 1];
                    int x3 = c.coords[i] / n;
                    int y3 = c.coords[i] % n;
                    c.board[x3][y3] = i;
                    // System.out.println("insert " + i + " at " + x3 + " " + y3 + " " +
                    // Arrays.toString(c.coords));
                }
                c.coords[0] = nC;
                c.board[x2][y2] = 0;
                children.add(c);
                c.parents.add(this);
            }
        }
    }
}