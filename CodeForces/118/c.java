import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int size = Integer.parseInt(tokenizer.nextToken());
            long h = Long.parseLong(tokenizer.nextToken());
            long h2 = h;
            long[] arr = new long[size];
            tokenizer = new StringTokenizer(in.readLine());
            long[] diff = new long[size];
            for (int i = 0; i < size; i++) {
                arr[i] = Long.parseLong(tokenizer.nextToken());
            }
            Arrays.sort(diff);
            for (int i = 0; i < size - 1; i++) {
                diff[i] = arr[i + 1] - arr[i];
            }
            Arrays.sort(diff);
            diff[diff.length - 1] = Long.MAX_VALUE;
            // System.out.println(Arrays.toString(diff));
            long k = 0;
            for (int i = 0; i < diff.length - 1; i++) {
                long e = Math.min((h2 + size - i - 1) / (size - i), diff[i + 1] - diff[i]);
                k += e;
                h2 -= e * (size - i);
                // System.out.println("x" + h2 + " " + e + " " + d + " " + diff[i + 1] + " " +
                // diff[i]);
                if (h2 <= 0)
                    break;
            }
            b.append(k + "\n");
        }
        System.out.print(b);
        in.close();
    }
}