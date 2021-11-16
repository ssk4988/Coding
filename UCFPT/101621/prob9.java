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
            double[] widths = new double[numRows];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < numRows; i++) {
                widths[i] = Double.parseDouble(tokenizer.nextToken());
            }
            // System.out.println(Arrays.toString(widths));
            double low = 0;
            double high = 1000000;
            // low = high;
            while ((high - low) > 1e-8) {
                double mid = (low + high) / 2;
                boolean solve = solve(widths, mid, numTrees);
                // System.out.println(low + " " + mid + " " + high + " " + solve);
                if (solve) {
                    low = mid;
                } else {
                    high = mid;
                }
            }
            // System.out.println(low + " " + high);
            // System.out.println(solve(widths, 1200, numTrees));
            System.out.printf("%.3f\n", low);
        }
        in.close();
        // out.close();
    }

    public static boolean solve(double[] widths, double val, int trees) {
        int left = trees;
        for (int i = 0; i < widths.length; i++) {
            left -= Math.max(0, (int) (widths[i] / val) - 1);
        }
        return left <= 0;
    }
}