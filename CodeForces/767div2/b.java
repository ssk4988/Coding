import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int l = Integer.parseInt(tokenizer.nextToken());
            int r = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            boolean works = false;
            if (l == r && l > 1) {
                works = true;
            } else if (l + 1 == r && k >= 1) {
                works = true;
            } else {
                int numnot2 = 0;
                if ((r - l + 1) % 2 == 0) {
                    numnot2 = (r - l + 1) / 2;
                } else {
                    numnot2 = (r - l + 1) / 2 + (l % 2 == 0 ? 0 : 1);
                }
                if (k >= numnot2) {
                    works = true;
                }
            }
            if (works) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
        in.close();
        out.close();
    }
}