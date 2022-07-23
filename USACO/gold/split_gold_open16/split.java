/*
ID: ssk49881
LANG: JAVA
TASK: split
*/

import java.io.*;
import java.util.*;

public class split {
    public static int numCows;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("split.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("split.out")));

        numCows = Integer.parseInt(in.readLine());
        Tuple[] cows = new Tuple[numCows];
        long minX = Integer.MAX_VALUE;
        long minY = Integer.MAX_VALUE;
        long maxX = Integer.MIN_VALUE;
        long maxY = Integer.MIN_VALUE;
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            long x = Integer.parseInt(tokenizer.nextToken());
            long y = Integer.parseInt(tokenizer.nextToken());
            cows[i] = new Tuple(x, y);
            if (x > maxX)
                maxX = x;
            if (x < minX)
                minX = x;
            if (y > maxY)
                maxY = y;
            if (y < minY)
                minY = y;
        }
        Arrays.sort(cows);

        long area1 = (maxX - minX) * (maxY - minY);
        long area2 = Long.MAX_VALUE;

        long[] areas = solve(cows);
        for (int i = 0; i < areas.length; i++) {
            if (areas[i] < area2)
                area2 = areas[i];
        }
        for (int i = 0; i < cows.length; i++) {
            long tmp = cows[i].x;
            cows[i].x = cows[i].y;
            cows[i].y = tmp;
        }
        Arrays.sort(cows);
        areas = solve(cows);
        for (int i = 0; i < areas.length; i++) {
            if (areas[i] < area2)
                area2 = areas[i];
        }

        out.println(area1 - area2);

        in.close();
        out.close();
    }

    public static long[] solve(Tuple[] cows) {
        TreeSet<Tuple> lower = new TreeSet<>(new TupleComp());
        TreeSet<Tuple> upper = new TreeSet<>(new TupleComp());
        long[] areas = new long[numCows];
        Arrays.fill(areas, Long.MAX_VALUE);
        for (int i = 0; i < numCows; i++) {
            upper.add(cows[i]);
        }
        long[][][] bounds = new long[2][2][2];
        bounds[0][0][0] = cows[0].x;
        bounds[1][0][1] = cows[numCows - 1].x;
        

        for (int i = 0; i < numCows - 1; i++) {
            lower.add(cows[i]);
            upper.remove(cows[i]);
            // System.out.println(lowerIndex);

            bounds[0][0][1] = cows[i].x;
            bounds[0][1][0] = lower.first().y;
            bounds[0][1][1] = lower.last().y;
            bounds[1][0][0] = cows[i + 1].x;
            bounds[1][1][0] = upper.first().y;
            bounds[1][1][1] = upper.last().y;

            areas[i] = (bounds[0][0][1] - bounds[0][0][0]) * (bounds[0][1][1] - bounds[0][1][0])
                    + (bounds[1][0][1] - bounds[1][0][0]) * (bounds[1][1][1] - bounds[1][1][0]);

            /*
             * System.out.println(areas[i]); System.out.println(lower.size() + " " +
             * upper.size() + " " + bounds[0][0][0] + " " + bounds[0][0][1] + " " +
             * bounds[0][1][0] + " " + bounds[0][1][1] + " " + bounds[1][0][0] + " " +
             * bounds[1][0][1] + " " + bounds[1][1][0] + " " + bounds[1][1][1]);
             */
            // System.out.println(lower);
            // System.out.println(upper);
        }
        return areas;
    }

    public static class TupleComp implements Comparator<Tuple> {
        @Override
        public int compare(split.Tuple o1, split.Tuple o2) {
            if (o1.y == o2.y) {
                if(o1.x < o2.x)return -1;
                if(o1.x>o2.x)return 1;
                return 0;
            }
            if (o1.y<o2.y)return -1;
            return 1;
        }
    }

    public static class Tuple implements Comparable<Tuple> {
        long x;
        long y;

        public Tuple(long x, long y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(split.Tuple o) {
            if (this.x == o.x) {
                if(this.y < o.y)return -1;
                if(this.y>o.y)return 1;
                return 0;
            }
            if (this.x<o.x)return -1;
            return 1;
        }

        @Override
        public String toString() {
            return "(" + this.x + "," + this.y + ")";
        }
    }
}