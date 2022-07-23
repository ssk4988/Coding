/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int x = Integer.parseInt(tokenizer.nextToken());
        int y = Integer.parseInt(tokenizer.nextToken());
        int[][] board = new int[x + 2][y + 2];
        for (int i = 0; i < x + 2; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < y + 2; j++) {
                board[i][j] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        int[][] b = new int[x + 2][y + 2];
        for (int i = 0; i < x + 2; i++) {
            for (int j = 0; j < y + 2; j++) {
                int sum = board[i][j];

                if (j > 1 && i > 1) {
                    sum -= b[i - 1][j - 1];
                }
                if (i > 1) {
                    sum -= b[i - 1][j];
                }
                if (i > 1 && j < y + 1) {
                    sum -= b[i - 1][j + 1];
                }
                if (j > 1)
                    sum -= b[i][j - 1];
                sum -= b[i][j];
                if (j < y + 1)
                    sum -= b[i][j + 1];
                if (i < x + 1 && j > 1)
                    sum -= b[i + 1][j - 1];
                if (i < x + 1)
                    sum -= b[i + 1][j];
                if (i < x + 1 && j < y + 1) {
                    sum -= b[i + 1][j + 1];
                }
                if (i + 1 < x + 2 && j + 1 < y + 2) {
                    b[i + 1][j + 1] = sum;
                }
            }
        }
        for (int i = 0; i < x + 2; i++) {
            // System.out.println(Arrays.toString(b[i]));
        }
        boolean works = true;
        for (int i = 0; i < x + 2; i++) {
            for (int j = 0; j < y + 2; j++) {
                if (i - 1 >= 0 && i + 1 < x + 2 && j - 1 >= 0 && j + 1 < y + 2) {
                    if (b[i][j] < 0 || b[i][j] > 1)
                        works = false;
                } else {
                    if (b[i][j] != 0)
                        works = false;
                }
            }
        }
        int[][] test = new int[x + 2][y + 2];
        for (int i = 0; i < x + 2; i++) {
            for (int j = 0; j < y + 2; j++) {
                for (int i2 = -1; i2 < 2 && i + i2 >= 0 && i + i2 < x + 2; i2++) {
                    for (int j2 = -1; j2 < 2 && j + j2 >= 0 && j + j2 < y + 2; j2++) {
                        test[i + i2][j + j2] += b[i][j];
                    }
                }
            }
        }
        for (int i = 0; i < x + 2; i++) {
            for (int j = 0; j < y + 2; j++) {
                if (board[i][j] != test[i][j]) {
                    works = false;
                }
            }
        }
        if (works) {
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    System.out.print(b[i + 1][j + 1] == 1 ? "X" : ".");
                }
                System.out.println();
            }
        } else {
            System.out.println("impossible");
        }

        in.close();
        out.close();
    }
}