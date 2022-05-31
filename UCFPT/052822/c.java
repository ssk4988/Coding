import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        StringBuilder b= new StringBuilder();
        while(!(line = in.readLine()).equals("0 0 0 0 0 0")){
            StringTokenizer tokenizer =new StringTokenizer(line);
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            int[] arr = new int[]{Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken())};
            int t = Integer.parseInt(tokenizer.nextToken());
            int[][] matrix =new int[n][n];
            for(int i = 0; i < n; i++){
                for(int j = -1; j < 2; j++){
                    if(i + j >= 0 && i + j < n){
                        matrix[i][i + j] = arr[j + 1];
                    }
                }
            }
            int[][] vector = new int[n][1];
            tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i <n; i++){
                vector[i][0] = Integer.parseInt(tokenizer.nextToken());
            }
            int[][] matrix2 = exp(matrix, m, t);
            int[][] answer = mult(matrix2, vector, m);
            for(int i = 0; i < n; i++){
                b.append(answer[i][0] + (i + 1 < n ? " " : "\n"));
            }
        }
        System.out.print(b);

        in.close();
    }
    public static int[][] mult(int[][] m1, int[][] m2, int m){
        int[][] result = new int[m1.length][m2[0].length];
        for(int i = 0; i < m1.length; i++){
            for(int j = 0; j < m2[0].length; j++){
                for(int k = 0; k< m1[i].length; k++){
                    result[i][j] += m1[i][k] * m2[k][j];
                    if(result[i][j] >= m) result[i][j] %= m;
                }
            }
        }
        return result;
    }
    public static int[][] exp(int[][] matrix, int m, int t){
        if(t == 0) {
            int[][] i = new int[matrix.length][matrix.length];
            for(int j = 0; j < matrix.length; j++){
                i[j][j] = 1;
            }
            return i;
        }
        if(t == 1) return matrix;
        int[][] a = exp(matrix, m, t / 2);
        a = mult(a, a, m);
        if(t % 2 == 1){
            a = mult(a, matrix, m);
        }
        return a;
    }
}