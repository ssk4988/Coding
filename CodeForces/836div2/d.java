import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        cas: for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            int minRange = n - 1;
            long msum = trisum(n);
            // case out 1, 2, 3, 4
            for (int r = minRange; true; r++) {
                long offset = 0;
                long minSum = trisum(r + 1) - trisum(offset);
                long targetSum = (long)r * r;
                if (targetSum < msum)
                    continue;
                int numRemove = r + 1 - n;
                long minError = trisum(numRemove + 1 + offset) - trisum(1 + offset);
                long maxError = trisum(r + offset) - trisum(r - numRemove + offset);
                long low = 0;
                long high = 400000;
                while (low < high) {
                    offset = low + (high - low) / 2;
                    minSum = trisum(r + 1 + offset) - trisum(offset);
                    minError = trisum(numRemove + 1 + offset) - trisum(1 + offset);
                    maxError = trisum(r + offset) - trisum(r - numRemove + offset);
                    if (minSum - minError >= targetSum) {
                        high = offset;
                    } else {
                        low = offset + 1;
                    }
                }
                offset = low;
                minSum = trisum(r + 1 + offset) - trisum(offset);
                minError = trisum(numRemove + 1 + offset) - trisum(1 + offset);
                maxError = trisum(r + offset) - trisum(r - numRemove + offset);
                if (minSum - maxError <= targetSum) {
                    // System.out.println("WE Win");
                    HashSet<Long> ans = new HashSet<>();
                    for (long i = 1 + offset; i <= 1 + offset + r; i++) {
                        ans.add(i);
                    }
                    long[] rem = new long[numRemove];
                    for (int i = 0; i < rem.length; i++) {
                        rem[i] = 1 + offset + r - numRemove + i;
                        minSum -= rem[i];
                    }
                    long lb = offset + 2;
                    for (int i = 0; i < rem.length; i++) {
                        long dec = Math.min(rem[i] - lb, targetSum - minSum);
                        minSum += dec;
                        rem[i] -= dec;
                        lb = rem[i] + 1;
                        ans.remove(rem[i]);
                    }
                    int cnt = 0;
                    for (long l : ans) {
                        out.append(l);
                        if (cnt + 1 < n) {
                            out.append(" ");
                        } else {
                            out.append("\n");
                        }
                        cnt++;
                    }
                    // out.append("Solved at range: " + r + " starting at " + (1 + offset) + " and ending at " + (1 + offset + r) + "\n");
                    continue cas;
                }
            }

        }
        System.out.print(out);
        in.close();
    }

    static long trisum(long k) {
        return k * (k + 1) / 2;
    }
}