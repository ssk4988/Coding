/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int i = 0; i < numcases; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int casenum = Integer.parseInt(tokenizer.nextToken());
            double d = Double.parseDouble(tokenizer.nextToken());
            double v1 = Double.parseDouble(tokenizer.nextToken());
            double v2 = Double.parseDouble(tokenizer.nextToken());
            double f = Double.parseDouble(tokenizer.nextToken());
            System.out.printf("%d %.2f%n", casenum, d / (v1+v2)*f);
        }

        in.close();
        out.close();
    }
}