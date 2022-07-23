import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int r = Integer.parseInt(tokenizer.nextToken());
            int c = Integer.parseInt(tokenizer.nextToken());
            boolean[][] board = new boolean[r][c];
            for (int j = 0; j < r / 2; j++) {
                for (int k = 0; k < c / 2; k++) {
                    board[2 * j][2 * k] = board[2 * j + 1][2 * k + 1] = (j + k) % 2 == 0;
                    board[2 * j + 1][2 * k] = board[2 * j][2 * k + 1] = (j + k) % 2 != 0;
                }
            }
            for (int j = 0; j < r; j++) {
                for (int k = 0; k < c; k++) {
                    b.append((board[j][k] ? 1 : 0) + (k + 1 < c ? " " : "\n"));
                }
            }
        }
        System.out.print(b);
        in.close();
    }
}