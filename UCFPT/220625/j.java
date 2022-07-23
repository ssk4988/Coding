import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());

        in.close();
    }
    public static void hungarian(int[][] matrix){
        int[][] m = new int[matrix.length][matrix[0].length];
        for(int i = 0; i < matrix.length; i++){
            for(int j = 0; j <  matrix[i].length; j++){
                m[i][j] = matrix[i][j];
            }
        }
        
    }
}