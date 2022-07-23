import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<Integer> rem = new ArrayList<>();
            if (n == 1) {
                System.out.println(3);
                continue;
            }
            rem.add(3 % n);
            while (rem.size() < 1000) {
                rem.add((rem.get(rem.size() - 1) * 10) % n);
            }
            // System.out.println(rem);
            long[] dp = new long[n];
            Arrays.fill(dp, Long.MAX_VALUE);
            dp[0] = 0;
            long bit = 1;
            outer: for (int i = 0; i < rem.size(); i++) {
                long[] dp2 = new long[n];
                for (int j = 0; j < n; j++) {
                    dp2[j] = dp[j];
                }
                int r = rem.get(i);
                for (int j = 0; j < dp.length; j++) {
                    if (dp[j] == Long.MAX_VALUE)
                        continue;
                    int index = (j + r)%dp.length;
                    long val = dp[j] | bit;
                    if (dp[index] == 0 || dp[index] > val) {
                        dp2[index] = val;
                    }
                }
                bit <<= 1;
                dp = dp2;
                // System.out.println(Arrays.toString(dp));
                if (dp[0] > 0)
                    break;
            } 
            bit = 1;
            long val2 = dp[0];
            // System.out.println(dp[0]);
            StringBuilder b = new StringBuilder();
            for (int i = 0; i < rem.size() && val2 > 0; i++) {
                if ((bit & val2) > 0) {
                    val2 ^= bit;
                    b.append('3');
                } else {
                    b.append('0');
                }
                bit <<= 1;
            }
            System.out.println(b.reverse());
        }
        in.close();
        out.close();
    }
}