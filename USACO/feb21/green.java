import java.io.*;
import java.util.*;

public class green {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int dim = Integer.parseInt(in.readLine());
        int[][] board = new int[dim][dim];
        for(int i = 0; i < dim; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for(int j = 0; j < dim; j++){
                board[i][j] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        int[][] nextRightsmall = new int[dim][dim];
        for(int i = 0; i < dim; i++){
            int c = dim;
            for(int j = dim - 1; j >= 0; j++){
                if(board[i][j] < 100){
                    c = j;
                }
                nextRightsmall[i][j] = c;
            }
        }
        int[][] nextLeftsmall = new int[dim][dim];
        for(int i = 0; i < dim; i++){
            int c = -1;
            for(int j = 0; j < dim; j++){
                if(board[i][j] < 100){
                    c = j;
                }
                nextLeftsmall[i][j] = c;
            }
        }
        int[][] nextRightequal = new int[dim][dim];
        for(int i = 0; i < dim; i++){
            int c = dim;
            for(int j = dim - 1; j >= 0; j++){
                if(board[i][j] == 100){
                    c = j;
                }
                nextRightequal[i][j] = c;
            }
        }
        int[][] nextLeftequal = new int[dim][dim];
        for(int i = 0; i < dim; i++){
            int c = -1;
            for(int j = 0; j < dim; j++){
                if(board[i][j] == 100){
                    c = j;
                }
                nextLeftequal[i][j] = c;
            }
        }

        in.close();
        // out.close();
    }
}