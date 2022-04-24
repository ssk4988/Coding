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
                    prefV[i][j] += prefV[i][j-1];
                }
            }
            int ans = 0;
            int nCellV = n / 2;
            for(int i = 0; i < n-1; i++){
                for(int j = 0; j < numH; j++){
                    for(int k = 1; i + k-1 < prefV[0].length && j + k-1 < prefH[0].length; k++){
                        int top = prefH[i][j + k-1] - (j>0 ? prefH[i][j-1] : 0);
                        int bottom = prefH[i+k][j + k-1] - (j>0 ? prefH[i+k][j-1] : 0);
                        int left = prefV[j][i + k-1] - (i>0 ? prefV[j][i-1] : 0);
                        int right = prefV[j+k][i + k-1] - (i>0 ? prefV[j+k][i-1] : 0);
                        if(top == k && bottom == k && left == k && right == k){
                            ans++;
                            //System.out.println(i + " " + j + " " + k);
                        }
                    }
                }
            }
            System.out.println(ans);
        }
        in.close();
        out.close();
    }
}