/*
ID: ssk49881
LANG: JAVA
TASK: triangles
*/

import java.io.*;
import java.util.*;

public class triangles {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("triangles.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("triangles.out")));
        Map<Integer, ArrayList<Point>> vertical = new HashMap<>();
        Map<Integer, ArrayList<Point>> horizontal = new HashMap<>();
        int numPoints = Integer.parseInt(in.readLine());
        ArrayList<Point> plist = new ArrayList<>();
        long answer = 0;
        for (int i = 0; i < numPoints; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if (!vertical.containsKey(x)) {
                vertical.put(x, new ArrayList<>());
            }
            if (!horizontal.containsKey(y)) {
                horizontal.put(y, new ArrayList<>());
            }
            Point p = new Point(x, y);
            horizontal.get(y).add(p);
            vertical.get(x).add(p);
            plist.add(p);
        }
        for (Map.Entry<Integer, ArrayList<Point>> entry : horizontal.entrySet()) {
            ArrayList<Point> hlist = entry.getValue();
            Collections.sort(hlist, new CompX());
            int firstx = hlist.get(0).x;
            long sum = 0;
            for (Point p : hlist) {
                sum += p.x - firstx;
            }
            int prevx = firstx;
            long prevsum = sum;
            for (int i = 0; i < hlist.size(); i++) {
                Point p = hlist.get(i);
                p.horizontalsum = prevsum + i * (p.x - prevx) - (hlist.size() - i) * (p.x - prevx);
                prevx = p.x;
                prevsum = p.horizontalsum;
            }
        }
        for (Map.Entry<Integer, ArrayList<Point>> entry : vertical.entrySet()) {
            ArrayList<Point> vlist = entry.getValue();
            Collections.sort(vlist, new CompY());
            int firsty = vlist.get(0).y;
            long sum = 0;
            for (Point p : vlist) {
                sum += p.y - firsty;
            }
            int prevy = firsty;
            long prevsum = sum;
            for (int i = 0; i < vlist.size(); i++) {
                Point p = vlist.get(i);
                p.verticalsum = prevsum + i * (p.y - prevy) - (vlist.size() - i) * (p.y - prevy);
                prevy = p.y;
                prevsum = p.verticalsum;
            }
        }
        for (Point p : plist) {
            answer += p.horizontalsum * p.verticalsum;
        }
        answer %= 1000000007;
        out.println(answer);

        in.close();
        out.close();
    }

    public static class CompX implements Comparator<Point> {
        @Override
        public int compare(triangles.Point o1, triangles.Point o2) {
            return o1.x - o2.x;
        }
    }

    public static class CompY implements Comparator<Point> {
        @Override
        public int compare(triangles.Point o1, triangles.Point o2) {
            return o1.y - o2.y;
        }
    }

    public static class Point {
        int x;
        int y;
        long verticalsum = -1;
        long horizontalsum = -1;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}