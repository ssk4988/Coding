import java.io.*;
import java.util.*;

public class appledivision {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        long[] dp = new long[1 << n];
        long[] val = new long[n];
        for(int i = 0; i < n ;i++){
            val[i] = Long.parseLong(tokenizer.nextToken());
            dp[1 << i] = val[i];
        }
        for(int i = 1; i < dp.length; i++){
            int j = i & (i-1);
            dp[i] = dp[i-j] + dp[j];
        }
        long diff = Long.MAX_VALUE;
        for(int i = 0; i < dp.length; i++){
            int j = (1 << n) - i - 1;
            diff = Math.min(Math.abs(dp[i] - dp[j]), diff);
        }
        System.out.println(diff);

        in.close();
    }
}