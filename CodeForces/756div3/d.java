/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        outer: for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            int[] parent = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int root = 0;
            for(int i = 0; i < n ;i++){
                parent[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                if(i == parent[i]) root = i;
            }
            int[] perm = new int[n];
            int[] rperm = new int[n];
            tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n ;i++){
                perm[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                rperm[perm[i]] = i;
            }
            if(rperm[root] != 0){
                //System.out.print("Case " + casenum + ": ");
                System.out.println(-1);
                continue outer;
            }
            for(int i = 0; i < n; i++){
                if(rperm[parent[i]] > rperm[i]){
                    //System.out.print("Case " + casenum + ": ");
                    System.out.println(-1);
                    continue outer;
                }
            }
            int[] weights = new int[n];
            Arrays.fill(weights, -1);
            int[] vals = new int[n];
            Arrays.fill(vals, -1);
            vals[root] = 0;
            weights[root] = 0;
            boolean solvable = true;
            for(int i = 0; i < n; i++){
                solve(i, vals, weights, parent, rperm, solvable);
            }
            //System.out.print("Case " + casenum + ": ");
            for(int i = 0; i < n; i++){
                System.out.print(weights[i]);
                if(i < n-1) System.out.print(" ");
            }
            System.out.println();
        }
        in.close();
        out.close();
    }
    public static void solve(int i, int[] vals, int[] weights, int[] parent, int[] rperm, boolean solvable){
        if(vals[i] != -1) return;
        if(vals[parent[i]] == -1) solve(parent[i], vals, weights, parent, rperm, solvable);
        weights[i] = rperm[i] - vals[parent[i]];
        vals[i] = rperm[i];
        if(weights[i] < 1) solvable = false;
    }
}