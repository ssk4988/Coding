import java.io.*;
import java.util.*;

public class p097 {
    public static int mod = 1000000007;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<Boolean>[] s = new ArrayList[2];
            for (int i = 0; i < s.length; i++) {
                s[i] = new ArrayList<>();
                String s1 = in.readLine();
                for (int j = 0; j < s1.length(); j++) {
                    if (s1.charAt(j) == '1') {

                    } else {
                        if(s1.charAt(j) == '0'){
                            s[i] = new ArrayList<>();
                        }
                        s[i].add(s1.charAt(j) != '+');
                    }

                }
            }
            int[][][] dp = new int[n + 5][n + 5][2];
            dp[0][0][0] = 1;
            long answer = 0;
            for (int i = 0; i <= s[0].size(); i++) {
                for (int j = 0; j <= s[1].size(); j++) {
                    for (int k = 0; k < dp[i][j].length; k++) {
                        if(i == s[0].size() && j == s[1].size()){
                            answer += dp[i][j][k];
                            answer %= mod;
                        }
                        else{
                            dp[i][j + 1][1] += dp[i][j][k];
                            if (dp[i][j + 1][1] >= mod) {
                                dp[i][j + 1][1] %= mod;
                            }
                            if(k == 0){
                                dp[i + 1][j][0] += dp[i][j][k];
                                if (dp[i + 1][j][0] >= mod) {
                                    dp[i + 1][j][0] %= mod;
                                }
                            }
                            else{
                                if (j > 0 && i < s[0].size() && s[0].get(i) != s[1].get(j - 1)) {
                                    dp[i + 1][j][0] += dp[i][j][k];
                                    if (dp[i + 1][j][0] >= mod) {
                                        dp[i + 1][j][0] %= mod;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            //System.out.println(dp[dp.length - 1][dp[0].length - 1][0] + " " + dp[dp.length - 1][dp[0].length - 1][1]);
            System.out.println(answer);
        }
        in.close();
    }
}