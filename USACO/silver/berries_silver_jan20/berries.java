/*
ID: ssk49881
LANG: JAVA
TASK: berries
*/

import java.io.*;
import java.util.*;

public class berries {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("berries.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("berries.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numTrees = Integer.parseInt(tokenizer.nextToken());
        int numBaskets = Integer.parseInt(tokenizer.nextToken());
        int[] berriesPerTree = new int[numTrees];
        int maxBerries = 0;
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numTrees; i++) {
            berriesPerTree[i] = Integer.parseInt(tokenizer.nextToken());
            if (berriesPerTree[i] > maxBerries) {
                maxBerries = berriesPerTree[i];
            }
        }
        int maxberriesBessie = 0;
        for (int maxPerTree = 1; maxPerTree <= maxBerries; maxPerTree++) {
            int basketNum = 0;
            int berriesBessie = 0;
            int[] berriesPerTreeCopy = new int[numTrees];
            for (int i = 0; i < numTrees; i++) {
                basketNum += berriesPerTree[i] / maxPerTree;
                berriesPerTreeCopy[i] = berriesPerTree[i];
            }
            if (basketNum < numBaskets / 2) {
                continue;
            }
            int berrybasketnum = maxPerTree;
            int numBasketsUsed = 0;
            while (numBasketsUsed < numBaskets && berrybasketnum >= 0) {
                for (int i = 0; i < numTrees; i++) {
                    while (berriesPerTreeCopy[i] >= berrybasketnum && numBasketsUsed < numBaskets) {
                        if (numBasketsUsed >= numBaskets / 2) {
                            berriesBessie += berrybasketnum;
                        }
                        numBasketsUsed++;
                        berriesPerTreeCopy[i] -= berrybasketnum;
                    }
                }
                berrybasketnum--;
            }
            maxberriesBessie = Math.max(maxberriesBessie, berriesBessie);
        }
        out.println(maxberriesBessie);

        in.close();
        out.close();
    }
}