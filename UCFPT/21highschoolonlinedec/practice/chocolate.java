import java.io.*;
import java.util.*;

public class chocolate {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numJudges = Integer.parseInt(tokenizer.nextToken());
            int numProblems = Integer.parseInt(tokenizer.nextToken());
            int[] starts = new int[numProblems];
            int[] ends = new int[numProblems];
            int[] startnum = new int[numJudges+1];
            for (int i = 0; i < numProblems; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                starts[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                ends[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                startnum[starts[i]]++;
            }
            int ans = numProblems;
            for(int i = 0; i < numProblems; i++){
                if(startnum[ends[i]+1] > 0){
                    ans--;
                    startnum[ends[i]+1]--;
                }
            }
            System.out.println(ans);
        }

        in.close();
        out.close();
    }
}