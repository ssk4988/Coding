import java.io.*;
import java.util.*;

public class coins {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCoins = Integer.parseInt(tokenizer.nextToken());
        int target = Integer.parseInt(tokenizer.nextToken());
        int[] coins = new int[numCoins];
        tokenizer = new StringTokenizer(in.readLine());
        for(int i = 0; i < numCoins; i++){
            coins[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(coins);
        int[] ways = new int[target + 1];
        Arrays.fill(ways, Integer.MAX_VALUE);
        ways[0] = 0;
        for(int i = 1; i < ways.length; i++){
            for(int c : coins){
                if(i - c >= 0 && ways[i - c] != Integer.MAX_VALUE){
                    ways[i] = Math.min(ways[i - c] + 1, ways[i]);
                }
            }
            //System.out.println(ways[i]);
        }
        int answer = ways[target] == Integer.MAX_VALUE ? -1 : ways[target];
        System.out.println(answer);

        in.close();
    }
}