import java.io.*;
import java.util.*;

public class ascii {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            String[] input = new String[n];
            int maxLen = 0;
            for(int i = 0; i < n; i++){
                input[i] = in.readLine();
                maxLen = Math.max(maxLen, input[i].length());
            }
            int numH = maxLen / 2;
            int numV = n;
            int[][] prefH = new int[n][numH];
            int[][] prefV = new int[numH+1][n-1];
            for(int i = 0; i < n; i++){
                for(int j = 0; j < input[i].length(); j++){
                    if(i > 0 && j % 2 == 0){
                        prefV[j / 2][i-1] += input[i].charAt(j) == '|' ? 1 : 0;
                    }
                    if(j % 2 == 1){
                        prefH[i][(j-1)/2] += input[i].charAt(j) == '_' ? 1 : 0;
                    }
                }
            }
            for(int i = 0; i < prefH.length; i++){
                for(int j = 1; j < prefH[i].length; j++){
                    prefH[i][j] += prefH[i][j-1];
                }
            }
            for(int i = 0; i < prefV.length; i++){
                for(int j = 1; j < prefV[i].length; j++){
                    prefH[i][j] += prefV[i][j-1];
                }
            }
            int ans = 0;
            int nCellV = n / 2;
            for(int i = 0; i < nCellV; i++){
                for(int j = 0; j < numH; j++){

                }
            }
        }
        in.close();
        out.close();
    }
}