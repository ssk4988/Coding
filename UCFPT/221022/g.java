import java.io.*;
import java.util.*;

public class g {
    public static double precision = 1e-3;
    public static double oo = 200;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new BufferedInputStream(System.in));
        PrintWriter out = new PrintWriter(new File("nl1.out"));
        int cn = 1;
        long start = System.currentTimeMillis();
        while (true) {
            int n = in.nextInt();
            if (n == 0)
                break;
            ArrayList<Double> p = new ArrayList<>();
            while (p.size() < n + 1 || p.size() < 2) {
                p.add(0.);
            }
            for (int i = 0; i < n + 1; i++) {
                p.set(n - i, in.nextDouble());

            }
            double c = in.nextDouble();

            double low = -oo;
            double high = oo;
            while (Math.abs(high - low) > precision) {
                double l1 = low + (high - low) / 3;
                double l2 = low + 2 * (high - low) / 3;
                double[] sc1 = calcscorey(c, l1, p);
                double[] sc2 = calcscorey(c, l2, p);
                if (sc1[0] < sc2[0]) {
                    high = l2;
                } else {
                    low = l1;
                }
            }
            double[] sc = calcscorey(c, low, p);
            // System.out.println("c Y: " + low);
            // System.out.println(Arrays.toString(sc));
            out.printf("Case %d: %.3f %.3f %.3f %.3f\n", cn, sc[2], sc[1], sc[4], sc[3]);
            cn++;
        }
        out.println("Duration: " + (System.currentTimeMillis() - start));
        in.close();
        out.close();
    }
    // String getStr(double k){
    // String s = String.format("%.3f", k);
    // if(s.equals("))
    // }

    public static double[] linearize(double x, double y, double a) {
        return new double[] { y - a * x, a };
    }

    public static ArrayList<Double> sq(ArrayList<Double> p) {
        ArrayList<Double> p1 = new ArrayList<>();
        while (p1.size() < p.size() * 2 - 1) {
            p1.add(0.);
        }
        for (int i = 0; i < p.size(); i++) {
            for (int j = 0; j < i; j++) {
                p1.set(i + j, p1.get(i + j) + 2 * p.get(i) * p.get(j));
            }
            p1.set(2 * i, p1.get(2 * i) + p.get(i) * p.get(i));
        }
        return p1;
    }

    public static double calc(ArrayList<Double> p, double x) {
        double ans = 0;
        for (int i = 0; i < p.size(); i++) {
            ans += Math.pow(x, i) * p.get(i);
        }
        return ans;
    }

    public static ArrayList<Double> integrate(ArrayList<Double> p) {
        ArrayList<Double> p1 = new ArrayList<>();
        while (p1.size() < p.size() + 1) {
            p1.add(0.);
        }
        for (int i = 0; i < p.size(); i++) {
            p1.set(i + 1, p.get(i) / (i + 1));
        }
        return p1;
    }

    public static double integrate(ArrayList<Double> p, double b1, double b2) {
        ArrayList<Double> p1 = integrate(p);
        return calc(p1, b2) - calc(p1, b1);
    }

    public static double[] calcscorey(double x, double y, ArrayList<Double> p) {
        double low = -oo;
        double high = oo;
        while (Math.abs(high - low) > precision) {
            double l1 = low + (high - low) / 3;
            double l2 = low + 2 * (high - low) / 3;
            double[] line1 = linearize(x, y, l1);
            double[] line2 = linearize(x, y, l2);
            p.set(0, p.get(0) - line1[0]);
            p.set(1, p.get(1) - line1[1]);
            ArrayList<Double> p1 = sq(p);
            p.set(0, p.get(0) + line1[0]);
            p.set(1, p.get(1) + line1[1]);
            p.set(0, p.get(0) - line2[0]);
            p.set(1, p.get(1) - line2[1]);
            ArrayList<Double> p2 = sq(p);
            p.set(0, p.get(0) + line2[0]);
            p.set(1, p.get(1) + line2[1]);
            if (integrate(p1, -1, x) < integrate(p2, -1, x)) {
                high = l2;
            } else {
                low = l1;
            }
        }
        double s1 = low;
        low = -oo;
        high = oo;
        while (Math.abs(high - low) > precision) {
            double l1 = low + (high - low) / 3;
            double l2 = low + 2 * (high - low) / 3;
            double[] line1 = linearize(x, y, l1);
            double[] line2 = linearize(x, y, l2);
            p.set(0, p.get(0) - line1[0]);
            p.set(1, p.get(1) - line1[1]);
            ArrayList<Double> p1 = sq(p);
            p.set(0, p.get(0) + line1[0]);
            p.set(1, p.get(1) + line1[1]);
            p.set(0, p.get(0) - line2[0]);
            p.set(1, p.get(1) - line2[1]);
            ArrayList<Double> p2 = sq(p);
            p.set(0, p.get(0) + line2[0]);
            p.set(1, p.get(1) + line2[1]);

            if (integrate(p1, x, 1) < integrate(p2, x, 1)) {
                high = l2;
            } else {
                low = l1;
            }
        }
        double s2 = low;

        double[] line1 = linearize(x, y, s1);
        double[] line2 = linearize(x, y, s2);
        p.set(0, p.get(0) - line1[0]);
        p.set(1, p.get(1) - line1[1]);
        ArrayList<Double> p1 = sq(p);
        p.set(0, p.get(0) + line1[0]);
        p.set(1, p.get(1) + line1[1]);
        p.set(0, p.get(0) - line2[0]);
        p.set(1, p.get(1) - line2[1]);
        ArrayList<Double> p2 = sq(p);
        p.set(0, p.get(0) + line2[0]);
        p.set(1, p.get(1) + line2[1]);
        return new double[] { integrate(p1, -1, x) + integrate(p2, x, 1), line1[0], line1[1], line2[0], line2[1] };
    }

}