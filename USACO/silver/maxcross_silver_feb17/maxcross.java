/*
ID: ssk49881
LANG: JAVA
TASK: maxcross
*/

import java.io.*;
import java.util.*;

public class maxcross {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("maxcross.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("maxcross.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numPaths = Integer.parseInt(tokenizer.nextToken());
        int numCont = Integer.parseInt(tokenizer.nextToken());
        int numBrk = Integer.parseInt(tokenizer.nextToken());
        boolean[] paths = new boolean[numPaths];
        Arrays.fill(paths, true);
        for (int i = 0; i < numBrk; i++) {
            int num = Integer.parseInt(in.readLine()) - 1;
            paths[num] = false;
        }
        int[] sum = new int[numPaths];
        sum[0] = paths[0] ? 1 : 0;
        for (int i = 1; i < numPaths; i++) {
            sum[i] = paths[i] ? sum[i - 1] + 1 : sum[i - 1];
        }
        int[] brkCont = new int[numPaths + 1 - numCont];
        brkCont[0] = numCont - sum[numCont - 1];
        for (int i = 1; i < numPaths + 1 - numCont; i++) {
            brkCont[i] = numCont - (sum[numCont + i - 1] - sum[i - 1]);
        }
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < brkCont.length; i++) {
            if (brkCont[i] < min) {
                min = brkCont[i];
            }
        }
        out.println(min);

        in.close();
        out.close();
    }
}