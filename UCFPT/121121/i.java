import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            long[] vals = new long[n];
            boolean[] white = new boolean[n];
            long[] ratio = new long[2];

            for (int i = 0; i < n; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                vals[i] = Long.parseLong(tokenizer.nextToken());
                white[i] = tokenizer.nextToken().equals("W");
                ratio[white[i] ? 1 : 0] += vals[i];
            }
            if (ratio[1] == 0) {
                out.append(ratio[0] + "\n");
                continue;
            }
            if (ratio[0] == 0) {
                out.append(ratio[1] + "\n");
                continue;
            }
            reduce(ratio);
            long nblocks = 0;
            int curr = 0;
            while (curr < n) {
                long[] block = new long[2];
                while (curr < n) {
                    int type = white[curr] ? 1 : 0;
                    long target = block[1 - type] / ratio[1 - type] * ratio[type];
                    if (block[1 - type] == 0 || block[1 - type] % ratio[1 - type] != 0 || block[type] > target) {
                        block[type] += vals[curr++];
                        continue;
                    }
                    long inc = Math.min(vals[curr], target - block[type]);
                    block[type] += inc;
                    vals[curr] -= inc;
                    if (vals[curr] <= 0) {
                        curr++;
                    }
                    if (block[type] == target) {
                        break;
                    }
                }
                nblocks++;
            }
            out.append(nblocks + "\n");
        }
        System.out.print(out);
        in.close();
    }

    public static long gcd(long a, long b) {
        if (b == 0)
            return a;
        if (a < b) {
            long tmp = a;
            a = b;
            b = tmp;
        }
        return gcd(b, a % b);
    }

    public static void reduce(long[] o) {
        long gcd = gcd(o[0], o[1]);
        o[0] /= gcd;
        o[1] /= gcd;
    }
}