/*
ID: ssk49881
LANG: JAVA
TASK: prob1
*/

import java.io.*;
import java.util.*;

public class prob1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int[] flowers = new int[n];
        int[] sums = new int[n + 1];
        sums[0] = 0;
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            flowers[i] = Integer.parseInt(tokenizer.nextToken());
            sums[i + 1] = sums[i] + flowers[i];
        }
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int s = Integer.parseInt(tokenizer.nextToken());
            int f = Integer.parseInt(tokenizer.nextToken());
            out.println(sums[f] - sums[s - 1]);
        }

        in.close();
        out.close();
    }
}