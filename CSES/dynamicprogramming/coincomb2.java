import java.io.*;
import java.util.*;
 
public class coincomb2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCoins = Integer.parseInt(tokenizer.nextToken());
        int start = Integer.parseInt(tokenizer.nextToken());
        int[] coins = new int[numCoins];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numCoins; i++) {
            coins[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(coins);
        int[][] ways = new int[start + 1][numCoins];
        Arrays.fill(ways[0], 1);
        for (int i = 1; i < ways.length; i++) {
            for (int j = 0; j < numCoins; j++) {
                int c = coins[j];
                /*if(j > 0){
                    ways[i][j] += ways[i][j - 1];
                }
                ways[i][j] += ways[i - c][j];*/
                //for (int k = 0; k <= j; k++) {
                //    ways[i][j] += ways[i - c][k];
                //}
                if(i - c >= 0){
                    ways[i][j] += ways[i - c][j];
                }
                if(j > 0){
                    ways[i][j] += ways[i][j - 1];
                }
                ways[i][j] %= 1000000007;
            }
        }
        System.out.println(ways[start][numCoins - 1]);
        in.close();
    }
}