/*
ID: ssk49881
LANG: JAVA
TASK: c
*/

import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numBuckets = Integer.parseInt(tokenizer.nextToken());
        int capacity = Integer.parseInt(tokenizer.nextToken());
        int[] weights = new int[numBuckets];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numBuckets; i++) {
            weights[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(weights);
        int doublesum = 0;
        int doubles = 0;
        int index1 = 0;
        int index2 = weights.length - 1;
        
        // System.out.println(Arrays.toString(weights));
        while (index1 < index2) {
            // System.out.printf("%d %d %d %d %n", index1, index2, weights[index1],
            // weights[index2]);
            if (weights[index1] + weights[index2] <= capacity) {
                doubles++;
                index1++;
                index2--;
            } else {
                index2--;
            }
        }
        System.out.println(numBuckets - doubles);
        in.close();
        out.close();
    }
}