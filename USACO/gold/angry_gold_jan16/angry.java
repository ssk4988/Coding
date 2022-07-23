/*
ID: ssk49881
LANG: JAVA
TASK: angry
*/

import java.io.*;
import java.util.*;

public class angry {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("angry.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
        int n1 = Integer.parseInt(in.readLine());

        Map<Integer, Integer> rev = new HashMap<>();
        TreeSet<Integer> set = new TreeSet<>();
        for (int i = 0; i < n1; i++) {
            set.add(Integer.parseInt(in.readLine()));
        }
        int[] loc = new int[set.size()];
        int n = 0;
        for (int i : set) {
            loc[n] = i;
            rev.put(i, n);
            n++;
        }
        int[][] dp = new int[n][2];
        for (int[] i : dp) {
            Arrays.fill(i, 1000000009);
        }
        dp[0][0] = dp[n - 1][1] = 0;
        for (int i = 1; i < n; i++) {
            int low = 0;
            int high = Math.max(dp[i - 1][0] + 1, loc[i] - loc[i - 1]);
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (dp[rev.get(set.ceiling(loc[i] - mid))][0] < mid) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            dp[i][0] = low;
        }
        for (int i = n - 1 - 1; i >= 0; i--) {
            int low = 0;
            int high = Math.max(dp[i + 1][1] + 1, loc[i + 1] - loc[i]);
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (dp[rev.get(set.floor(loc[i] + mid))][1] < mid) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            dp[i][1] = low;
        }
        int minPower = set.last() - set.first();
        for (int i = 0; i < n; i++) {
            int low = 0;
            int high = set.last() - set.first();
            while (low < high) {
                int mid = low + (high - low) / 2;
                double mid2 = mid / 2.0;
                int i1 = rev.get(set.floor(loc[i] + mid));
                if (dp[i][0] + 1 <= mid2 && dp[i1][1] + 1 <= mid2) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            minPower = Math.min(minPower, low);
        }
        out.printf("%.1f\n", minPower / 2.0);

        in.close();
        out.close();
    }
}