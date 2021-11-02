/*
ID: ssk49881
LANG: JAVA
TASK: diamond
*/

import java.io.*;
import java.util.*;

public class diamond {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("diamond.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("diamond.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numDiamonds = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int[] diamonds = new int[numDiamonds];
        for (int i = 0; i < numDiamonds; i++) {
            diamonds[i] = Integer.parseInt(in.readLine());
        }
        int[] lsums = new int[numDiamonds];
        int[] rsums = new int[numDiamonds];
        Arrays.sort(diamonds);
        int p1 = 0;
        int p2 = 0;
        int maxP1 = 0;
        int maxP2 = 0;
        while (p2 < numDiamonds && p1 < numDiamonds) {
            while (p2 < numDiamonds && diamonds[p2] - diamonds[p1] <= k) {
                if (p2 - p1 > maxP2 - maxP1) {
                    maxP1 = p1;
                    maxP2 = p2;
                }
                lsums[p2] = 1 + Math.max(p2 - p1, maxP2 - maxP1);
                p2++;
            }
            p2--;
            p1++;
        }
        p1 = numDiamonds - 1;
        p2 = numDiamonds - 1;
        maxP1 = numDiamonds - 1;
        maxP2 = numDiamonds - 1;
        while (p2 >= 0 && p1 >= 0) {
            while (p1 >= 0 && diamonds[p2] - diamonds[p1] <= k) {
                if (p2 - p1 > maxP2 - maxP1) {
                    maxP1 = p1;
                    maxP2 = p2;
                }
                rsums[p1] = 1 + Math.max(p2 - p1, maxP2 - maxP1);
                p1--;
            }
            p1++;
            p2--;
        }

        int max = 0;
        for (int i = 0; i < numDiamonds - 1; i++) {
            max = Math.max(max, lsums[i] + rsums[i + 1]);
        }
        out.println(max);

        in.close();
        out.close();
    }
}