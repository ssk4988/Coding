import java.io.*;
import java.util.*;

public class pair2 {
    public static int mod = 1000000007;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            char[][] s = new char[2][];
            boolean[][] s2 = new boolean[2][];
            int[] nvar = new int[2];
            int[][] nummult = new int[2][];
            for (int i = 0; i < nummult.length; i++) {
                String s1 = in.readLine();
                int last0 = -1;
                for (int j = 0; j < s1.length(); j++) {
                    if (s1.charAt(j) == '0')
                        last0 = j;
                }
                s[i] = s1.substring(last0 + 1).toCharArray();
                s2[i] = new boolean[s[i].length];
                for(int j = 0; j +last0 + 1 < s1.length(); j++){
                    s2[i][j] = s1.charAt(j + last0 + 1) == '+';
                }
                /*
                for (int j = 0; j < s[i].length; j++) {
                    if (s[i][j] == '+')
                        nvar[i]++;
                }
                nummult[i] = new int[nvar[i] + 1];
                int varcnt = 0;
                for (int j = 0; j < s[i].length; j++) {
                    if (s[i][j] == '+')
                        varcnt++;
                    else {
                        int num = s[i][j] - '0';
                        if (num != 1) {
                            nummult[i][varcnt]++;
                        }
                    }
                }
                */
            }
            int[][][] dp = new int[s[0].length + 1][s[1].length + 1][2];
            dp[0][0][0] = 0;
            dp[0][0][1] = 0;
            for(int i = 0; i< dp.length; i++){
                for(int j = 0; j < dp[i].length; j++){
                    for(int k = 0; k < dp[i][j].length; k++){
                        if(j+1 < dp[i].length){
                            dp[i][j+1][1] += dp[i][j][k];
                            if(dp[i][j+1][1] >= mod){
                                dp[i][j+1][1] %= mod;
                            }
                        }
                    }
                }
            }
        }
        in.close();
    }
}