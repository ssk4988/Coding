import java.io.*;
import java.util.*;

public class commutative {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine(), "=");
            tokenizer.nextToken();
            int target = Integer.parseInt(tokenizer.nextToken());
            tokenizer = new StringTokenizer(in.readLine(), ",");
            int n = tokenizer.countTokens();
            int[] vals = new int[n];
            for (int i = 0; i < n; i++) {
                vals[i] = Integer.parseInt(tokenizer.nextToken());
            }
            boolean[] use = new boolean[n];
            solve(use, 0, vals, target, b);
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static void solve(boolean[] use, int index, int[] vals, int target, StringBuilder b) {
        if (index == use.length) {
            int sum = 0;
            for (int i = 0; i < use.length; i++) {
                if (use[i])
                    sum += vals[i];
            }
            if (sum == target) {
                int cnt = 0;
                for (int i = 0; i < use.length; i++) {
                    if (use[i]) {
                        if (cnt > 0) {
                            b.append("+");
                        }
                        b.append(vals[i]);
                        cnt++;
                    }
                }
                b.append("\n");

            }
            return;
        }
        for(int i = index; i < use.length; i++){
            solve(use, i+1, vals, target, b);
            use[i] = true;
            solve(use, i+1, vals, target, b);
            use[i] = false;
        }
    }
}