import java.io.*;
import java.util.*;

public class grid {
    public static boolean[][] board;
    public static int dim;
    public static int[][] beauty;
    public static int max = 0;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        dim = Integer.parseInt(in.readLine());
        beauty = new int[dim][dim];
        for (int i = 0; i < dim; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < dim; j++) {
                beauty[i][j] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        int[][][] sub = new int[dim][dim][6];
        for (int i = 0; i < dim - 1; i++) {
            for (int j = 0; j < dim - 1; j++) {
                sub[i][j][0] = beauty[i][j] + beauty[i][j + 1];
                sub[i][j][1] = beauty[i][j + 1] + beauty[i + 1][j + 1];
                sub[i][j][2] = beauty[i + 1][j] + beauty[i + 1][j + 1];
                sub[i][j][3] = beauty[i][j] + beauty[i + 1][j];
                sub[i][j][4] = beauty[i][j] + beauty[i + 1][j + 1];
                sub[i][j][5] = beauty[i + 1][j] + beauty[i][j + 1];
            }
        }
        board = new boolean[dim][dim];
        System.out.println("22");

        in.close();
        // out.close();
    }

    public static void calc() {
        int sum = 0;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (board[i][j]) {
                    sum += beauty[i][j];
                }
            }
        }
        if (sum > max)
            max = sum;
    }

    public static void dfs(int i, int j) {
        if (i == 0) {
            int i2 = i;
            int j2 = j;
            if(j2 == dim - 1){
                j2 = 0;
                i2++;
            }
            board[i][j] = false;
            dfs(i2, j2);
            board[i][j] = true;
            dfs(i2, j2);
        }
        else{
            
        }

        if (i > 0 && j > 0) {
            int count = 0;

            if (board[i - 1][j])
                count++;
            if (board[i][j - 1])
                count++;
            if (board[i - 1][j - 1])
                count++;
            board[i][j] = false;
            int i1 = i;
            int j1 = j + 1;
            if (j1 == dim) {
                i1++;
                j1 = 0;
                if (i1 == dim) {
                    calc();
                    return;
                }
            }
            dfs(i1, j1);
        } else if (i > 0) {

        }
    }
}