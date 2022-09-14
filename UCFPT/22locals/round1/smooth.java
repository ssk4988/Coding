import java.io.*;
import java.util.*;

public class smooth {
    public static double precision = 1e-7;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int s = Integer.parseInt(tokenizer.nextToken());
        int[][] c = new int[n][2];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            c[i][0] = Integer.parseInt(tokenizer.nextToken());
            c[i][1] = Integer.parseInt(tokenizer.nextToken());
        }
        HashMap<Double, Integer> freq = new HashMap<>();
        double[] angles = new double[n];
        for (int i = 0; i < n; i++) {
            int[] adj = new int[] { (i + 1) % n, (i - 1 + n) % n };
            int[][] d = new int[2][2];
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    d[j][k] = c[adj[j]][k] - c[i][k];
                }
            }
            long dot = (long) (d[0][0]) * d[1][0] + d[0][1] * d[1][1];
            double cos = dot / Math.sqrt(Math.pow(d[0][0], 2) + Math.pow(d[0][1], 2))
                    / Math.sqrt(Math.pow(d[1][0], 2) + Math.pow(d[1][1], 2));
            angles[i] = Math.acos(cos) * 180 / Math.PI;
            angles[i] = 360 - angles[i];
            if (!freq.containsKey(angles[i])) {
                freq.put(angles[i], 0);
            }
            freq.put(angles[i], freq.get(angles[i]) + 1);
        }
        double low = 180;
        double high = 360;
        while (Math.abs(high - low) > precision) {
            double mid = (high + low) / 2;
            if (test(freq, mid, s)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        System.out.println(low);
        in.close();
    }

    public static boolean test(Map<Double, Integer> freq, double val, long limit) {
        long cur = 0;
        for (Map.Entry<Double, Integer> e : freq.entrySet()) {
            long low = 0;
            long high = limit + 1;
            while (low < high) {
                long mid = low + (high - low) / 2;
                if ((e.getKey() + 180 * mid) / (mid + 1) <= val) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            if (high > limit) {
                return false;
            }
            cur += high * e.getValue();
        }

        return cur <= limit;
    }
}