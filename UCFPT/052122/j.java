import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int w = Integer.parseInt(tokenizer.nextToken());
        int h = Integer.parseInt(tokenizer.nextToken());
        int n = Integer.parseInt(in.readLine());
        int numLines = 0;
        ArrayList<line> lines = new ArrayList<>();
        ArrayList<point> points = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int[][] coords = new int[2][2];
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    coords[j][k] = Integer.parseInt(tokenizer.nextToken());
                }
            }
            boolean[] edge = new boolean[2];
            for (int j = 0; j < 2; j++) {
                if (coords[j][0] == 0 || coords[j][0] == w || coords[j][1] == 0 || coords[j][1] == h)
                    edge[j] = true;
            }
            if (edge[0] && edge[1]) {
                point p1 = new point(cnt(coords[0][0], coords[0][1], w, h));
                point p2 = new point(cnt(coords[1][0], coords[1][1], w, h));
                line l = new line(numLines, p1, p2);
                numLines++;
                p1.l = l;
                p2.l = l;
                points.add(p1);
                points.add(p2);
            }
        }
        Collections.sort(points);
        boolean works = true;
        boolean[] used = new boolean[numLines];
        LinkedList<line> stack = new LinkedList<>();
        for (int i = 0; i < points.size(); i++) {
            if (used[points.get(i).l.id]) {
                if (stack.getFirst() != points.get(i).l) {
                    works = false;
                    break;
                }
                stack.removeFirst();
                used[points.get(i).l.id] = false;
            } else {
                stack.addFirst(points.get(i).l);
                used[points.get(i).l.id] = true;
            }
        }
        System.out.println(works ? "Y" : "N");
        in.close();

    }

    public static long cnt(long x, long y, long w, long h) {
        if (y == 0)
            return x;
        if (x == w)
            return w + y;
        if (y == h)
            return 2 * w + h - x;
        if (x == 0)
            return 2 * w + 2 * h - y;

        return 0;
    }

    public static class point implements Comparable<point> {
        long coord = 0;
        line l = null;

        public point(long coord) {
            this.coord = coord;
        }

        @Override
        public int compareTo(j.point o) {
            if (this.coord < o.coord)
                return -1;
            if (this.coord > o.coord)
                return 1;
            return 0;
        }
    }

    public static class line {
        int id = 0;
        point p1 = null;
        point p2 = null;

        public line(int id, point p1, point p2) {
            this.p1 = p1;
            this.p2 = p2;
            this.id = id;
        }
    }
}