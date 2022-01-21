import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] arr = new int[n];
            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;
            for(int i = 0; i < n; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
                min = Math.min(min, arr[i]);
                max = Math.max(max, arr[i]);
            }
            System.out.println(max - min);
        }
        in.close();
        out.close();
    }
}