import java.io.*;
import java.util.*;

public class prob9 {

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int k = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            int[] v = new int[n];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                v[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int[] vals = new int[n];
            Arrays.fill(vals, 0);
            long[] ans = test(vals, 0, v, k);
            System.out.printf("%.5f%n", ans[1] == 0 ? 0 : (double) ans[0] / ans[1]);
        }

        in.close();
        out.close();
    }

    public static long[] test(int[] vals, int t, int[] v, int k) {
        long[] ans = {0, 0};
        if (t == k) {
            boolean works = true;
            ans[1]++;
            for (int i : vals) {
                if (i == 0) {
                    works = false;
                    break;
                }
            }

            if (works) {
                ans[0]++;
            }
            return ans;
        }
        for (int i = 0; i < vals.length; i++) {
            if (vals[i] >= v[i])
                continue;
            vals[i]++;
            long[] output = test(vals, t + 1, v, k);
            ans[0] += (v[i] - vals[i] + 1) * output[0];
            ans[1] += (v[i] - vals[i] + 1) * output[1];
            vals[i]--;
        }
        return ans;
    }
}