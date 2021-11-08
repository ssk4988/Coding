import java.io.*;
import java.util.*;

public class prob9 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int numTimes = Integer.parseInt(in.readLine());
        for (int count = 0; count < numTimes; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numRows = Integer.parseInt(tokenizer.nextToken());
            int numTrees = Integer.parseInt(tokenizer.nextToken());
            long[] widths = new long[numRows];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < numRows; i++) {
                widths[i] = (long) (Double.parseDouble(tokenizer.nextToken()) * 10000);
            }
            // System.out.println(Arrays.toString(widths));
            long low = -1;
            long high = 1000000 * 10000;
            // low = high;
            while (low < high) {
                long mid = low + (high - low + 1) / 2;
                boolean solve = solve(widths, mid, numTrees);
                // System.out.println(low + " " + mid + " " + high + " " + solve);
                if (solve) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            // System.out.println(low + " " + high);
            // System.out.println(solve(widths, 1200, numTrees));
            System.out.printf("%.3f\n", (double) (low / 10) / 1000);
        }
        in.close();
        // out.close();
    }

    public static boolean solve(long[] widths, long val, int trees) {
        int left = trees;
        for (int i = 0; i < widths.length; i++) {
            left -= widths[i] / val - 1;
        }
        return left <= 0;
    }
}