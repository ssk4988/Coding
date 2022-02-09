import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            if (k == 1 || n % 2 == 0) {
                System.out.println("YES");
                int odd = 1;
                int even = 2;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < k; j++) {
                        if (i % 2 == 0) {
                            System.out.print(odd + " ");
                            odd += 2;
                        } else {
                            System.out.print(even + " ");
                            even += 2;
                        }
                    }
                    System.out.println();
                }
            } else {
                System.out.println("NO");
            }
        }
        in.close();
        out.close();
    }
}