import java.io.*;
import java.util.*;

public class prob11 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int r = Integer.parseInt(tokenizer.nextToken());
            int v = Integer.parseInt(tokenizer.nextToken());
            System.out.printf("Case %d: %.8f\n", (casenum + 1), (double) r * Math.PI / 2 / v);
        }

        in.close();
        out.close();
    }
}