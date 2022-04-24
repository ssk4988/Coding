import java.io.*;
import java.util.*;

public class taxi {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int[] dist = new int[3];
            point[] ps = new point[3];
            TreeSet<point>[] points =new TreeSet[3];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < 3; i++) {
                int x = Integer.parseInt(tokenizer.nextToken());
                int y = Integer.parseInt(tokenizer.nextToken());
                dist[i] = Integer.parseInt(tokenizer.nextToken());
                ps[i] = new point(x, y);
                points[i] = new TreeSet<>();
                int x1 = x - dist[i];
                int y1 = y;
                for(; x1 < x; x1++, y1++){
                    point p = new point(x1, y1);
                    points[i].add(p);
                }
                for(; x1 < x + dist[i]; x1++, y1--){
                    point p = new point(x1, y1);
                    points[i].add(p);
                }
                for(; x1 > x; x1--, y1--){
                    point p = new point(x1, y1);
                    points[i].add(p);
                }
                for(; x1 > x - dist[i]; x1--, y1++){
                    point p = new point(x1, y1);
                    points[i].add(p);
                }
            }
            TreeSet<point> ans = new TreeSet<>();
            ans.addAll(points[0]);
            ans.retainAll(points[1]);
            ans.retainAll(points[2]);
            System.out.println("(" + ans.first().x + "," + ans.first().y + ")");
        }

        in.close();
        out.close();
    }

    public static class point implements Comparable<point> {
        int x;
        int y;

        public point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(taxi.point o) {
            if (this.x == o.x)
                return this.y - o.y;
            return this.x - o.x;
        }
    }
}