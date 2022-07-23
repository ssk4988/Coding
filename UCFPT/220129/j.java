import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            long[] x = new long[n];
            long[] y = new long[n];
            long maxArea = 0;
            for (int i = 0; i < n; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                x[i] = Integer.parseInt(tokenizer.nextToken());
                y[i] = Integer.parseInt(tokenizer.nextToken());

            }
            long totalArea = shoelace(x, y, 0, n-1);
            for (int v1 = 0; v1 < n; v1++) {
                for (int v2 = 0; v2+1 < v1; v2++) {
                    if (v2 == 0 && v1 == n-1)
                        continue;
                    long area = shoelace(x, y, v2, v1);
                    area = Math.min(area, totalArea - area);
                    maxArea = Math.max(area, maxArea);
                }
            }
            System.out.println(maxArea);
        }

        in.close();
        out.close();
    }

    public static long shoelace(long[] x, long[] y, int v1, int v2) {
        int numV = v2 - v1 + 1;
        long area = 0;
        for (int i = v1; i <= v2; i++) {
            area += x[i] * y[i == v2 ? v1 : i + 1];
            area -= x[i] * y[i == v1 ? v2 : i - 1];
        }
        area = Math.abs(area);
        return area;
    }
}