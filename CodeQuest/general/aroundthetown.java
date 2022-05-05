import java.io.*;
import java.util.*;

public class aroundthetown {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        double precision = 0.000000001;
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int l = Integer.parseInt(tokenizer.nextToken());
            int s = Integer.parseInt(tokenizer.nextToken());
            landmark[] ls = new landmark[l];
            stop[] ss = new stop[s];
            for (int i = 0; i < l; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                int x = Integer.parseInt(tokenizer.nextToken());
                int y = Integer.parseInt(tokenizer.nextToken());
                ls[i] = new landmark(i, x, y);
            }
            for (int i = 0; i < s; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                int x = Integer.parseInt(tokenizer.nextToken());
                int y = Integer.parseInt(tokenizer.nextToken());
                ss[i] = new stop(i, x, y);
            }
            Arrays.sort(ss, new stopcomp());
            while (true) {
                for (int i = 0; i < s; i++) {
                    ss[i].marks = new ArrayList<>();
                }
                for (int i = 0; i < l; i++) {
                    int best = 0;
                    double bestdist = distance(ls[i], ss[0]);
                    for (int j = 0; j < s; j++) {
                        double dist = distance(ls[i], ss[j]);
                        if (dist < bestdist) {
                            best = j;
                            bestdist = dist;
                        }
                    }
                    ss[best].marks.add(ls[i]);
                }
                boolean quit = true;
                for (int i = 0; i < s; i++) {
                    ss[i].oldX = ss[i].x;
                    ss[i].oldY = ss[i].y;
                    ss[i].x = 0;
                    ss[i].y = 0;
                    for (landmark c : ss[i].marks) {
                        ss[i].x += c.x;
                        ss[i].y += c.y;
                    }
                    if (ss[i].marks.size() != 0) {
                        ss[i].x /= ss[i].marks.size();
                        ss[i].y /= ss[i].marks.size();
                    }
                    if (quit && (ss[i].x != ss[i].oldX || ss[i].y != ss[i].oldY)) {
                        quit = false;
                    }
                }

                if (quit)
                    break;
            }
            Arrays.sort(ss, new stopcomp2());
            for (int i = 0; i < s; i++) {
                System.out.printf("%.1f %.1f%n", ss[i].x, ss[i].y);
            }
        }

        in.close();
        out.close();
    }
    public static class stopcomp2 implements Comparator<stop>{
        @Override
        public int compare(aroundthetown.stop o1, aroundthetown.stop o2) {
            return o1.id - o2.id;
        }
    }
    public static class stopcomp implements Comparator<stop> {
        @Override
        public int compare(aroundthetown.stop o1, aroundthetown.stop o2) {
            if (o1.x == o2.x) {
                if (o1.y < o2.y)
                    return -1;
                if (o1.y == o2.y)
                    return 0;
                return 1;
            }
            if (o1.x < o2.x)
                return -1;
            return 1;
        }
    }

    public static double distance(landmark l, stop s) {
        return Math.pow(l.x - s.x, 2) + Math.pow(l.y - s.y, 2);
    }

    public static class landmark {
        int id;
        double dist = Double.MAX_VALUE;
        int x;
        int y;

        public landmark(int id, int x, int y) {
            this.id = id;
            this.x = x;
            this.y = y;
        }
    }

    public static class stop {
        int id;
        double x;
        double y;
        double oldX = 0, oldY = 0;
        ArrayList<landmark> marks = new ArrayList<>();

        public stop(int id, int x, int y) {
            this.id = id;
            this.x = x;
            this.y = y;
        }
    }

}