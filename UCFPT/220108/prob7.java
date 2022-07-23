import java.io.*;
import java.util.*;

public class prob7 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        double margin = 0.000000001;
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            int d = Integer.parseInt(tokenizer.nextToken());
            int w = Integer.parseInt(tokenizer.nextToken());
            double low = 0;
            double high = x;
            double best = Double.MAX_VALUE;
            double inc = (high - low) / 3;
            while(inc > margin) {
                inc = (high - low) / 3;
                double lt = findT(x, y, d, w, low + inc);
                double rt = findT(x, y, d, w, high - inc);
                if (lt < rt + margin) {
                    high -= inc;
                } else if (lt + margin > rt) {
                    low += inc;
                } else {
                    high -= inc;
                    low += inc;
                }
                best = Math.min(best, Math.min(lt, rt));
            }
            System.out.printf("%.3f\n", best);
        }

        in.close();
        out.close();
    }

    public static double findT(int x, int y, int d, int w, double z) {
        double t = z / d + Math.sqrt(Math.pow((double) x - z, 2) + Math.pow(y, 2)) / w;
        return t;
    }
}