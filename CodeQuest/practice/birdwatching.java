import java.io.*;
import java.util.*;

public class birdwatching {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            point[] ps = new point[x];
            for (int i = 0; i < x; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                ps[i] = new point(i, tokenizer.nextToken(), Double.parseDouble(tokenizer.nextToken()),
                        Double.parseDouble(tokenizer.nextToken()), Double.parseDouble(tokenizer.nextToken()),
                        Double.parseDouble(tokenizer.nextToken()));

            }
            yloop: for (int i = 0; i < y; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                point p = new point(i + x, "A", Double.parseDouble(tokenizer.nextToken()),
                        Double.parseDouble(tokenizer.nextToken()), Double.parseDouble(tokenizer.nextToken()),
                        Double.parseDouble(tokenizer.nextToken()));
                for (int j = 0; j < ps.length; j++) {
                    ps[j].dist = distance(ps[j], p);
                }
                Arrays.sort(ps, new pcomp());
                int k = 5;
                int[] cnt = new int[3];
                for (int j = 0; j < k; j++) {
                    cnt[ps[j].type]++;
                }
                int max = Math.max(cnt[0], Math.max(cnt[1], cnt[2]));
                int t = 0;
                for (int j = 0; j < cnt.length; j++) {
                    if (cnt[j] == max)
                        t++;
                }
                while (t > 1) {
                    cnt[ps[k].type]++;
                    k++;
                    max = Math.max(cnt[0], Math.max(cnt[1], cnt[2]));
                    t = 0;
                    for (int j = 0; j < cnt.length; j++) {
                        if (cnt[j] == max)
                            t++;
                    }
                }
                for (int j = 0; j < cnt.length; j++) {
                    if (cnt[j] == max) {
                        String o = "";
                        if (j == 0) {
                            o = "Accipitridae";
                        } else if (j == 1) {
                            o = "Passeridae";
                        } else {
                            o = "Cathartidae";
                        }
                        System.out.println(o);
                        continue yloop;
                    }
                }
            }
        }

        in.close();
        out.close();
    }

    public static double distance(point p1, point p2) {
        return Math.sqrt(Math.pow(p1.data[0] - p2.data[0], 2) + Math.pow(p1.data[1] - p2.data[1], 2)
                + Math.pow(p1.data[2] - p2.data[2], 2) + Math.pow(p1.data[3] - p2.data[3], 2));
    }

    public static class pcomp implements Comparator<point> {
        @Override
        public int compare(birdwatching.point o1, birdwatching.point o2) {
            if (o1.dist < o2.dist)
                return -1;
            if (o1.dist > o2.dist)
                return 1;
            return 0;
        }
    }

    public static class point {
        int id;
        int type = 0;
        double[] data = new double[4];
        double dist = Double.MAX_VALUE;

        public point(int id, String type, double w, double x, double y, double z) {
            data = new double[] { w, x, y, z };
            this.id = id;
            if (type.charAt(0) == 'A')
                this.type = 0;
            else if (type.charAt(1) == 'P')
                this.type = 1;
            else
                this.type = 2;
        }
    }
}