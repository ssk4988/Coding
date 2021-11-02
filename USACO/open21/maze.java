import java.io.*;
import java.util.*;

public class maze {
    public static int dim;
    public static boolean[][] reachable;
    public static place[][] places;
    public static boolean[][] isPlace;
    public static int cowI;
    public static int cowJ;
    public static boolean[][] visited;
    public static boolean[] reached = new boolean[19683];
    public static boolean[] terminal = new boolean[19683];
    ArrayList<place> queue = new ArrayList<>();
    public static int sp = 0;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        dim = Integer.parseInt(in.readLine());
        reachable = new boolean[dim][dim];
        places = new place[dim][dim];
        isPlace = new boolean[dim][dim];
        cowI = -1;
        cowJ = -1;
        for (int i = 0; i < dim; i++) {
            String s = in.readLine();
            for (int j = 0; j < dim; j++) {
                String s2 = s.substring(3 * j, 3 * j + 3);
                char c = s2.charAt(0);
                if (c == 'O' || c == 'M' || c == 'B') {
                    isPlace[i][j] = true;
                    places[i][j] = new place(i, j, s2);
                    // System.out.println(places[i][j].type + " " + places[i][j].bi + " " +
                    // places[i][j].bj);
                }
                if (c != '#') {
                    reachable[i][j] = true;
                }
                if (c == 'B') {
                    cowI = i;
                    cowJ = j;
                }
            }
        }
        reachable[cowI][cowJ] = false;
        dfs(cowI, cowJ, null);
        reachable[cowI][cowJ] = true;
        visited = new boolean[dim][dim];
        dfs3(places[cowI][cowJ]);
        visited = new boolean[dim][dim];
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (isPlace[i][j]) {
                }
            }
        }
        ArrayList<place> ps = new ArrayList<>();
        ps.addAll(places[cowI][cowJ].children);
        int[][] b = new int[3][3];
        dfs2(ps, b, -1);
        int answers = 0;
        for (int i = 0; i < reached.length; i++) {
            if (!reached[i]) {
                continue;
            }
            if (terminal[i]) {
                answers++;
            }

        }
        System.out.println(answers);

        in.close();
    }

    public static void dfs3(place p) {
        if (!visited[p.i][p.j]) {
            p.sp = sp;
            sp++;
            visited[p.i][p.j] = true;
            for (int i = p.children.size() - 1; i >= 0; i--) {
                dfs3(p.children.get(i));
            }
        }
    }

    public static void dfs2(ArrayList<place> queue, int[][] board, int sp) {
        int index = board[0][0] * 1 + board[0][1] * 3 + board[0][2] * 9 + board[1][0] * 27 + board[1][1] * 81
                + board[1][2] * 243 + board[2][0] * 729 + board[2][1] * 2187 + board[2][2] * 6561;
        reached[index] = true;
        int[] calc = new int[8];
        int inc = 1;
        for (int i2 = 0; i2 < 3; i2++) {
            calc[0] += board[i2][0] * inc;
            calc[1] += board[i2][1] * inc;
            calc[2] += board[i2][2] * inc;
            calc[3] += board[0][i2] * inc;
            calc[4] += board[1][i2] * inc;
            calc[5] += board[2][i2] * inc;
            calc[6] += board[i2][i2] * inc;
            calc[7] += board[i2][2 - i2] * inc;
            inc *= 3;
        }
        for (int i2 : calc) {
            if (i2 == 25 || i2 == 17) {
                terminal[index] = true;
            }
        }

        outer: for (int i = queue.size() - 1; i >= 0; i--) {

            place p = queue.get(i);
            if(terminal[index]){
                for(place p1 : p.parents){
                    if(p1.sp == sp){
                        queue.remove(i);
                        continue outer;
                    }
                }
            }
            if (p.sp < sp) {
                continue;
            }
            if (visited[p.i][p.j]) {
                continue;
            }
            ArrayList<place> queue2 = new ArrayList<>();
            queue2.addAll(queue);
            queue2.remove(i);
            for (int j = 0; j < p.children.size(); j++) {
                place c = p.children.get(j);
                if (!visited[c.i][c.j]) {
                    queue2.add(c);
                }
            }
            visited[p.i][p.j] = true;
            int[][] board2 = new int[3][3];
            for (int i2 = 0; i2 < 3; i2++) {
                for (int j = 0; j < 3; j++) {
                    board2[i2][j] = board[i2][j];
                }
            }
            if (board2[p.bi][p.bj] == 0) {
                board2[p.bi][p.bj] = p.type;
            }
            dfs2(queue2, board2, p.sp);
            visited[p.i][p.j] = false;
        }
    }

    public static void dfs(int i, int j, place p) {
        place p2 = p;
        if (isPlace[i][j]) {
            p2 = places[i][j];
            if (p != null) {
                p2.parents.add(p);
                p.children.add(p2);
                // System.out.println("parent:" + p.type + " " + p.bi + " " + p.bj + " " +
                // "child:" + p2.type + " " + p2.bi + " " + p2.bj + " ");
            }
        }
        if (i > 0 && reachable[i - 1][j]) {
            reachable[i - 1][j] = false;
            dfs(i - 1, j, p2);
            reachable[i - 1][j] = true;
        }
        if (j > 0 && reachable[i][j - 1]) {
            reachable[i][j - 1] = false;
            dfs(i, j - 1, p2);
            reachable[i][j - 1] = true;
        }
        if (i < dim - 1 && reachable[i + 1][j]) {
            reachable[i + 1][j] = false;
            dfs(i + 1, j, p2);
            reachable[i + 1][j] = true;
        }
        if (j < dim - 1 && reachable[i][j + 1]) {
            reachable[i][j + 1] = false;
            dfs(i, j + 1, p2);
            reachable[i][j + 1] = true;
        }
    }

    public static class place {
        int i;
        int j;
        int type;
        int bi;
        int bj;
        String s;
        int sp = -1;
        ArrayList<place> parents = new ArrayList<>();
        ArrayList<place> children = new ArrayList<>();

        public place(int i, int j, String s) {
            this.s = s;
            this.i = i;
            this.j = j;
            char c = s.charAt(0);
            if (c == 'M') {
                type = 1;
            } else if (c == 'O') {
                type = 2;
            } else {
                type = 3;
            }
            if (type == 3) {
                bi = 0;
                bj = 0;
            } else {
                bi = s.charAt(1) - '1';
                bj = s.charAt(2) - '1';
            }
        }
    }
}