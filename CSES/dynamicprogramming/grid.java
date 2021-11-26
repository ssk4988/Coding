import java.io.*;
import java.util.*;

public class grid {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int dim = Integer.parseInt(in.readLine());
        boolean[][] trap = new boolean[dim][dim];
        for (int i = 0; i < dim; i++) {
            String s = in.readLine();
            for (int j = 0; j < dim; j++) {
                if (s.charAt(j) == '*') {
                    trap[i][j] = true;
                }
            }
        }
        int[][] paths = new int[dim][dim];
        paths[0][0] = 1;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if(trap[i][j]){
                    paths[i][j] = 0;
                    continue;
                }
                if (i > 0 && !trap[i - 1][j]) {
                    paths[i][j] += paths[i - 1][j];
                }
                if (j > 0 && !trap[i][j - 1]) {
                    paths[i][j] += paths[i][j - 1];
                }
                paths[i][j] %= 1000000007;
            }
        }
        System.out.println(paths[dim - 1][dim - 1]);

        in.close();
    }
}