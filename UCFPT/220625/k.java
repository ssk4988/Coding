import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        double precision = 1e-8;
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] coords = new int[6];
            for (int i = 0; i < coords.length; i++) {
                coords[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int[] p = new int[] { Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()) };
            boolean intersects = false;
            int p1 = -1;
            int p2 = -1;
            floop: for (int i = 0; i < 3; i++) {
                for (int j = 0; j < i; j++) {
                    if (intersects(coords[2 * i], coords[2 * i + 1], coords[2 * j], coords[2 * j + 1], p[0],
                            p[1])) {
                        p1 = i;
                        p2 = j;
                        intersects = true;
                        break floop;
                    }
                }
            }
            if (!intersects) {
                b.append("-1\n");
                continue;
            }
            int p3 = 3 - p1 - p2;
            double[] dcoords = new double[coords.length];
            for (int i = 0; i < dcoords.length; i++) {
                dcoords[i] = coords[i];
            }
            double totarea = area(dcoords) / 2;

            dcoords[0] = coords[2 * p1];
            dcoords[1] = coords[2 * p1 + 1];
            dcoords[2] = p[0];
            dcoords[3] = p[1];
            dcoords[4] = coords[2 * p3];
            dcoords[5] = coords[2 * p3 + 1];
            if (area(dcoords) < totarea) {
                dcoords[0] = coords[2 * p2];
                dcoords[1] = coords[2 * p2 + 1];
            }
            double low1 = dcoords[0];
            double high1 = dcoords[4];
            double low2 = dcoords[1];
            double high2 = dcoords[5];
            for (int i = 0; i < 100; i++) {
                dcoords[4] = (low1 + high1) / 2;
                dcoords[5] = (low2 + high2) / 2;
                if (area(dcoords) < totarea) {
                    low1 = dcoords[4];
                    low2 = dcoords[5];
                } else {
                    high1 = dcoords[4];
                    high2 = dcoords[5];
                }
            }
            b.append(dcoords[4] + " " + dcoords[5] + "\n");
        }
        System.out.print(b);
        in.close();
    }

    public static double area(double[] coords) {
        double a = 0;
        for (int i = 0; i < coords.length; i += 2) {
            a += coords[i] * coords[(i + 3) % coords.length];
        }
        for (int i = 1; i < coords.length; i += 2) {
            a -= coords[i] * coords[(i + 1) % coords.length];
        }
        return Math.abs(a);
    }

    public static boolean intersects(int a1, int a2, int b1, int b2, int c1, int c2) {
        int ca1 = c1 - a1;
        int ca2 = c2 - a2;
        int ba1 = b1 - a1;
        int ba2 = b2 - a2;
        int crossmag = ca1 * ba2 - ca2 * ba1;
        if (crossmag != 0)
            return false;
        if (c1 <= Math.max(a1, b1) && c1 >= Math.min(a1, b1) && c2 <= Math.max(a2, b2) && c2 >= Math.min(a2, b2))
            return true;
        return false;
    }
}