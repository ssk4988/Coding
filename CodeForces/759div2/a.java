import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int len = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            boolean[] arr = new boolean[len];
            for (int i = 0; i < len; i++) {
                arr[i] = Integer.parseInt(tokenizer.nextToken()) == 1;
            }
            int height = 1;
            for (int i = 0; i < len; i++) {
                if (i >= 1 && !arr[i] && !arr[i - 1]) {
                    height = -1;
                    break;
                }
                if (i >= 1 && arr[i] && arr[i - 1]) {
                    height += 5;
                } else if (arr[i]) {
                    height++;
                }
            }
            System.out.println(height);
        }

        in.close();
        out.close();
    }
}