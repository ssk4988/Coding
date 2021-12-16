import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            StringBuilder s11 = new StringBuilder(tokenizer.nextToken());
            int p1 = Integer.parseInt(tokenizer.nextToken());
            tokenizer = new StringTokenizer(in.readLine());
            StringBuilder s12 = new StringBuilder(tokenizer.nextToken());
            int p2 = Integer.parseInt(tokenizer.nextToken());
            while (s11.length() < s12.length()) {
                s11.append('0');
                p1--;
            }
            while (s12.length() < s11.length()) {
                s12.append('0');
                p2--;
            }
            if (p1 != p2) {
                b.append((p1 > p2 ? ">" : "<") + "\n");
            } else {
                if (s11.toString().equals(s12.toString())) {
                    b.append("=\n");
                } else {
                    b.append((Integer.parseInt(s11.toString()) > Integer.parseInt(s12.toString()) ? ">" : "<") + "\n");
                }

            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}