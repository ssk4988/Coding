import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            int[] t = new int[n];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                t[i] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        in.close();
        out.close();
    }
}