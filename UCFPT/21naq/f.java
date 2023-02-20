import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String s= in.readLine();
        int n = s.length();
        boolean[] vowel = new boolean[n];
        int[] indices = new int[n];
        for(int i = 0; i < n; i++){
            vowel[i] = isVowel(s.charAt(i));
            if(s.charAt(i)>'Z'){
                indices[i] = s.charAt(i) + 26 - 'a';
            }
            else{
                indices[i] = s.charAt(i) - 'A';
            }
        }
        long mod = 1000000007;
        long[][] dp = new long[5][52];
        for(int i = 0; i < n; i++){
            if(vowel[i]){
                for(int j= 0; j < 52; j++){
                    if(j == indices[i]) continue;
                    dp[4][j] += dp[3][j];
                    dp[2][j] += dp[1][j];
                    dp[0][j]++;
                    if(dp[0][j] >= mod){
                        dp[0][j] %= mod;
                    }
                    
                }
            }
        }

        in.close();
        out.close();
    }
    public static boolean isVowel(char c){
        if(c == 'a' || c == 'A' || c=='e'||c=='E'||c=='i'||c=='I'||c=='o'||c=='O'||c=='u'||c=='U'){
            return true;
        }
        return false;
    }
}