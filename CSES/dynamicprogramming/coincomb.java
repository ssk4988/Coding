import java.io.*;
import java.util.*;

public class coincomb {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCoins = Integer.parseInt(tokenizer.nextToken());
        int start = Integer.parseInt(tokenizer.nextToken());
        int[] coins = new int[numCoins];
        tokenizer = new StringTokenizer(in.readLine());
        for(int i = 0; i < numCoins; i++){
            coins[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(coins);
        long[] ways = new long[start + 1];
        ways[0] = 1;
        for (int i = 0; i < ways.length; i++) {
            for (int c : coins) {
                if (i - c >= 0) {
                    ways[i] += ways[i - c];
                }
            }
            ways[i] %= 1000000007;
        }
        System.out.println(ways[start]);
        in.close();
    }
}