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
            for (int i = 0; i + 1 < size; i++) {
                diff[i] = arr[i + 1] - arr[i];
            }

            diff[diff.length - 1] = Long.MAX_VALUE;
            Arrays.sort(diff);
            // System.out.println(Arrays.toString(diff));
            long k = 0;
            long sum = 0;
            for (int i = 0; i < diff.length; i++) {
                long e = Math.min((h - sum + (size - i) - 1) / (size - i), diff[i] - k);
                k += e;
                sum += e * (size - i);
                // System.out.println(i + " " + sum + " " + k + " " + e);
                if (sum >= h)
                    break;
            }
            b.append(k + "\n");
        }
        System.out.print(b);
        in.close();
    }
}