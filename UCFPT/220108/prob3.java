import java.io.*;
import java.util.*;

public class prob3 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;
        while(!(line = in.readLine()).equals("0")){
            int n = Integer.parseInt(line);
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int[] v = new int[n];
            int[] d = new int[n];
            int vsum = 0;
            for(int i = 0; i < n; i++){
                v[i] = Integer.parseInt(tokenizer.nextToken());
                vsum += v[i];
            }
            tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                d[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int[] dp = new int[vsum + 1];
            Arrays.fill(dp, Integer.MAX_VALUE);
            dp[0] = 0;
            for(int i = 0; i < n; i++){
                for(int j = dp.length - 1 - v[i]; j >= 0; j--){
                    if(dp[j] == Integer.MAX_VALUE) continue;
                    dp[j + v[i]] = Math.min(dp[j+v[i]], dp[j] + d[i]);
                }
            }
            int min = Integer.MAX_VALUE;
            for(int j = vsum / 2 + 1; j < dp.length; j++){
                min = Math.min(min, dp[j]);
            }
            //System.out.println(Arrays.toString(dp));
            System.out.println(min);
        }

        in.close();
        out.close();
    }
}