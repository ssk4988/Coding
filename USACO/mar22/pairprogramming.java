import java.io.*;
import java.util.*;

public class pairprogramming {
    public static int mod = 1000000007;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            char[][] s = new char[2][];
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
            }
            int[][][][] dp = new int[nummult[0].length][nummult[1].length][][]; // [][][leftmults0][leftmults1]
            for (int i = 0; i < dp.length; i++) {
                for (int j = 0; j < dp[i].length; j++) {
                    dp[i][j] = new int[nummult[0][i] + 1][nummult[1][j] + 1];
                    if (i == 0 && j == 0) {
                        dp[i][j][nummult[0][0]][nummult[1][0]] = 1;
                        /*for (int k = 0; k < dp[i][j].length; k++) {
                            for (int l = 0; l < dp[i][j][k].length; l++) {
                                dp[i][j][k][l] = 1;
                            }
                        }*/

                    } else {
                        if (i > 0) {
                            for (int l = 0; l < dp[i][j][0].length; l++) {
                                for (int l2 = 0; l2 <= l; l2++) {
                                    dp[i][j][nummult[0][i]][l2] += dp[i - 1][j][nummult[0][i - 1]][l];
                                    if (dp[i][j][nummult[0][i]][l2] >= mod) {
                                        dp[i][j][nummult[0][i]][l2] -= mod;
                                    }
                                }
                            }
                        }
                        if (j > 0) {
                            for (int k = 0; k < dp[i][j].length; k++) {
                                for (int k2 = 0; k2 <= k; k2++) {
                                    dp[i][j][k2][nummult[1][j]] += dp[i][j - 1][k][nummult[1][j - 1]];
                                    if (dp[i][j][k2][nummult[1][j]] >= mod) {
                                        dp[i][j][k2][nummult[1][j]] -= mod;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            System.out.println();
        }
        in.close();
    }
}