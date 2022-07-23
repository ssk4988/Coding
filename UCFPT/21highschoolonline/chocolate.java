/*
ID: ssk49881
LANG: JAVA
TASK: chocolate
*/

import java.io.*;
import java.util.*;

public class chocolate {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for(int num = 0; num < n; num++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int maxJudge = Integer.parseInt(tokenizer.nextToken());
            int numProblems = Integer.parseInt(tokenizer.nextToken());
            int[] start = new int[numProblems];
            int[] end = new int[numProblems];
            int[] startfq = new int[maxJudge+1];
            for(int i = 0; i < numProblems; i++){
                tokenizer = new StringTokenizer(in.readLine());
                start[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                end[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                startfq[start[i]]++;
            }
            int ans = numProblems;
            for(int i = 0; i<numProblems; i++){
                if(startfq[end[i]+1]>0){
                    ans--;
                    startfq[end[i]+1]--;
                    
                }
            }
            System.out.println(ans);        
        }

        in.close();
        out.close();
    }
}