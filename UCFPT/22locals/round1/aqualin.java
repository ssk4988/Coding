import java.io.*;
import java.util.*;

public class aqualin {
    public static int[] dx = new int[] { 1, 0, -1, 0 };
    public static int[] dy = new int[] { 0, 1, 0, -1 };
    public static ArrayList<Integer> tcomp = new ArrayList<>();
    public static ArrayList<Integer> tsize = new ArrayList<>();
    public static ArrayList<Integer> ccomp = new ArrayList<>();
    public static ArrayList<Integer> csize = new ArrayList<>();
    public static int n;
    public static int[][] type;
    public static int[][] color;
    public static int[][] tc;
    public static int[][] cc;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(in.readLine());
        type = new int[n][n];
        color = new int[n][n];
        tc = new int[n][n];
        cc = new int[n][n];
        for (int[] i : tc) {
            Arrays.fill(i, -1);
        }
        for (int[] i : cc) {
            Arrays.fill(i, -1);
        }
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++) {
                type[i][j] = tokenizer.nextToken().charAt(0) - 'A';
                color[i][j] = Integer.parseInt(tokenizer.nextToken()) - 1;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tc[i][j] == -1) {
                    tcomp.add(type[i][j]);
                    tsize.add(0);
                    flood_fill(tcomp.size() - 1, tsize, type, tc, i, j);
                }
                if (cc[i][j] == -1) {
                    ccomp.add(color[i][j]);
                    csize.add(0);
                    flood_fill(ccomp.size() - 1, csize, color, cc, i, j);
                }
            }
        }
        int[] cans = new int[n];
        int[] tans = new int[26];
        for (int i = 0; i < tcomp.size(); i++) {
            tans[tcomp.get(i)] = Math.max(tans[tcomp.get(i)], tsize.get(i));
        }
        for (int i = 0; i < ccomp.size(); i++) {
            cans[ccomp.get(i)] = Math.max(cans[ccomp.get(i)], csize.get(i));
        }
        int cscore = 0;
        int tscore = 0;
        for (int i = 0; i < n; i++) {
            if (cans[i] > 1) {
                cscore += (cans[i] - 1) * cans[i] / 2;
            }
        }
        for (int i = 0; i < 26; i++) {
            if (tans[i] > 1) {
                tscore += (tans[i] - 1) * tans[i] / 2;
            }
        }
        System.out.println(tscore + " " + cscore);
        in.close();
    }

    public static void flood_fill(int component, ArrayList<Integer> complist, int[][] b, int[][] c, int x, int y) {
        ArrayDeque<int[]> q = new ArrayDeque<>();
        q.add(new int[] { x, y });
        while (!q.isEmpty()) {
            int[] a = q.poll();
            if (c[a[0]][a[1]] == -1) {
                c[a[0]][a[1]] = component;
                complist.set(component, complist.get(component) + 1);
                for (int i = 0; i < 4; i++) {
                    if (a[0] + dx[i] >= 0 && a[0] + dx[i] < n && a[1] + dy[i] >= 0 && a[1] + dy[i] < n
                            && b[a[0]][a[1]] == b[a[0] + dx[i]][a[1] + dy[i]]) {
                        q.add(new int[] { a[0] + dx[i], a[1] + dy[i] });
                    }
                }
            }
        }
    }
}