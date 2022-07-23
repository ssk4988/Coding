/*
ID: ssk49881
LANG: JAVA
TASK: h
*/

import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int count = 0; count < numcases; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int casenum = Integer.parseInt(tokenizer.nextToken());
            double ax = Double.parseDouble(tokenizer.nextToken());
            double ay = Double.parseDouble(tokenizer.nextToken());
            double bx = Double.parseDouble(tokenizer.nextToken());
            double by = Double.parseDouble(tokenizer.nextToken());
            double cx = Double.parseDouble(tokenizer.nextToken());
            double cy = Double.parseDouble(tokenizer.nextToken());
            double low = 0;
            double high = Math.PI / 6;
            double mid;
            while (low + 0.000001 < high) {

            }
        }

        in.close();
        out.close();
    }

    public static void test(double theta, double ax, double ay, double bx, double by, double cx, double cy) {
        double abangle = bx - ax == 0 ? Math.PI / 2 * (by > ay ? 1 : -1) : Math.atan((by - ay) / (bx - ax));
        double abslope = Math.tan(abangle + theta);
        double bcangle = cx - bx == 0 ? Math.PI / 2 * (cy > by ? 1 : -1) : Math.atan((cy - by) / (cx - bx));
        double bcslope = Math.tan(bcangle + theta);
        double caangle = ax - cx == 0 ? Math.PI / 2 * (ay > cy ? 1 : -1) : Math.atan((ay - cy) / (ax - cx));
        double caslope = Math.tan(caangle + theta);
        double broax = (ay - by - ax * abslope + bx * bcslope) / (bcslope - abslope);
        double broay = abslope * (broax - ax) + ay;
        double brobx = (by - cy - bx * bcslope + cx * caslope) / (caslope - bcslope);
        double broby = bcslope * (brobx - bx) + by;
    }
}