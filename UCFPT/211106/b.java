/*
ID: ssk49881
LANG: JAVA
TASK: b
*/

import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        long[][] ncr = new long[51][51];
        ncr[0][0] = 1;
        for(int i = 1; i <= 50; i++){
            for(int j = 0; j <= i; j++){
                if(j>0) ncr[i][j] += ncr[i-1][j-1];
                if(j<i) ncr[i][j] += ncr[i-1][j];
            }
        }
        //System.out.println(ncr[50][49]);
        for(int count = 0; count < numcases; count++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int casenum = Integer.parseInt(tokenizer.nextToken());
            int steps = Integer.parseInt(tokenizer.nextToken());
            steps /= 2;
            int step2 = steps / 2;
            int step1 = steps % 2;
            long ways = 0;
            while(step2 >= step1){
                long addend = ncr[step2+step1][step2];
                ways += addend * addend;
                step2--;
                step1 += 2;             
            }
            System.out.printf("%d %d%n", casenum, ways);
        }

        in.close();
        out.close();
    }
}