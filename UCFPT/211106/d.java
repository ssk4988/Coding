/*
ID: ssk49881
LANG: JAVA
TASK: d
*/

import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        int maxNum = 10000;
        ArrayList<Integer>[] divisors = new ArrayList[maxNum + 1];
        for (int i = 0; i < divisors.length; i++) {
            divisors[i] = new ArrayList<>();
        }
        for (int i = 2; i <= maxNum; i++) {
            if (divisors[i].size() > 0)
                continue;
            for (int j = 1; j * i <= maxNum; j++) {
                divisors[j * i].add(i);
                // System.out.printf("%d %d %d %d%n", i, j, divisors[i].size(),
                // divisors[j*i].size());
            }
        }
        int[] fareylength = new int[maxNum + 1];
        fareylength[0] = 0;
        fareylength[1] = 2;
        for (int i = 2; i < fareylength.length; i++) {
            int addend = 0;
            iterloop: for (int j = 1; j <= i; j++) {
                for (int d : divisors[i]) {
                    if (j % d == 0) {
                        continue iterloop;
                    }
                }
                addend++;
            }
            fareylength[i] = addend + fareylength[i - 1];
        }
        for (int count = 0; count < numcases; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int casenum = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            System.out.printf("%d %d%n", casenum, fareylength[n]);
        }

        in.close();
        out.close();
    }
}