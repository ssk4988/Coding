import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numCases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numCases; casenum++){
            int n = Integer.parseInt(in.readLine());
            int[] start = new int[n];
            int[] end = new int[n];
            boolean[][] f = new boolean[n+1][n+1];
            for(int i = 0; i < n;i ++){
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                start[i] = Integer.parseInt(tokenizer.nextToken());
                end[i] = Integer.parseInt(tokenizer.nextToken());
                f[start[i]][end[i]] = true;
            }
            ans: for(int i= 0; i < n; i++){
                for(int j = start[i]; j <= end[i]; j++){
                    boolean works = true;
                    if(j > start[i] && !f[start[i]][j-1]) works = false;
                    if(j < end[i] && !f[j+1][end[i]]) works = false;
                    if(works){
                        System.out.println(start[i] + " " + end[i] + " " + j);
                        continue ans;
                    }
                }
            }
        }
        in.close();
        out.close();
    }
}