import java.io.*;
import java.util.*;

public class breakice {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int moves = Integer.parseInt(tokenizer.nextToken());
        boolean[][] b = new boolean[n][n];
        boolean[] rows = new boolean[n];
        boolean[] cols = new boolean[n];
        Arrays.fill(rows, true);
        Arrays.fill(cols, true);
        for (int i = 0; i < n; i++) {
            Arrays.fill(b[i], true);
        }
        int inval = 0;
        for (int i = 0; i < moves; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int r = Integer.parseInt(tokenizer.nextToken()) - 1;
            int c = Integer.parseInt(tokenizer.nextToken()) - 1;
            if (!b[r][c]) {
                inval++;
                continue;
            }
            rows[r] = false;
            cols[c] = false;
            b[r][c] = false;
            for (int j = 0; j < n; j++) {
                check(b, rows, cols, r, j);
                check(b, rows, cols, j, c);
            }
        }
        System.out.println(inval);
        in.close();
    }

    public static void check(boolean[][] b, boolean[] rows, boolean[] cols, int r, int c) {
        if (!rows[r] && !cols[c])
            b[r][c] = false;
    }
}