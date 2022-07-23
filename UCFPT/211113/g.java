/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        long[] num = new long[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            num[i] = Long.parseLong(tokenizer.nextToken());
        }
        long[] d = new long[2];
        d[1] = Long.MAX_VALUE;
        long curr = 0;
        for (int i = 0; i < n; i++) {
            curr = num[i] - curr;
            d[(i + 1) % 2] = Math.min(d[(i + 1) % 2], curr);
            // System.out.println(curr);
        }
        long t = d[0];
        d[0] = d[0] - t;
        d[1] = d[1] + t;
        // System.out.println(Arrays.toString(d));
        long answer = Math.max(0, d[1] + 1);
        System.out.println(answer);
        in.close();
        out.close();
    }
}