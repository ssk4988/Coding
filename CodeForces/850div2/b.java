import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            long wc = Integer.parseInt(tokenizer.nextToken());
            long ws = Integer.parseInt(tokenizer.nextToken());
            long[] c = new long[n];
            long[] s = new long[n];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                c[i] = Integer.parseInt(tokenizer.nextToken());
            }
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                s[i] = Integer.parseInt(tokenizer.nextToken());
            }
            long minshift = Long.MIN_VALUE;
            long maxshift = Long.MAX_VALUE;
            for (int i = 0; i < n; i++) {
                long cleft = c[i] - wc, cright = c[i] + wc, sleft = s[i] - ws, sright = s[i] + ws;
                minshift = Math.max(minshift, Math.min(sleft - cleft, sright - cright));
                maxshift = Math.min(maxshift, Math.max(sleft - cleft, sright - cright));
            }
            System.out.println(minshift > maxshift ? "NO" : "YES");
        }
        in.close();
    }
}
