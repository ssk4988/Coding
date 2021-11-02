/*
ID: ssk49881
LANG: JAVA
TASK: cowjump
*/

import java.io.*;
import java.util.*;

public class cowjump {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("2.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new
        // FileWriter("cowjump.out")));
        int numLines = Integer.parseInt(in.readLine());
        ArrayList<Point> points = new ArrayList<>();
        ArrayList<Line> lines = new ArrayList<>();
        for (int i = 0; i < numLines; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x1 = Integer.parseInt(tokenizer.nextToken());
            int y1 = Integer.parseInt(tokenizer.nextToken());
            int x2 = Integer.parseInt(tokenizer.nextToken());
            int y2 = Integer.parseInt(tokenizer.nextToken());
            Point p1 = new Point(x1, y1);
            Point p2 = new Point(x2, y2);
            Line l = null;
            if (x1 < x2 || (x1 == x2 && y1 < y2)) {
                l = new Line(p1, p2, i);
            } else {
                l = new Line(p2, p1, i);
            }
            p1.line = l;
            p2.line = l;
            lines.add(l);
            points.add(p1);
            points.add(p2);
        }
        Collections.sort(points, new compX());
        int index = 0;
        int nextVal = 0;
        ArrayList<Line> intersections = new ArrayList<>();
        ArrayList<Point> active = new ArrayList<>();
        while (index < points.size()) {
            nextVal = points.get(index).x;
            while (points.get(index).x == nextVal) {
                Point p = points.get(index);
                if (p.line.added) {
                    p.line.added = false;
                    int pindex = Collections.binarySearch(active, p.line.p1, new compY());
                    if(pindex < 0){
                        System.out.println("error" + index + " " + p.line + " " + p.line.p1 + " " + p.line.p2);
                    }
                    if(pindex == 0 || pindex == active.size() - 1){

                    }
                    else{
                        if(active.get(pindex - 1).line.intersects(active.get(pindex + 1).line)){
                            ArrayList<Line> a = new ArrayList<>();
                            a.add(active.get(pindex - 1).line);
                            a.add(active.get(pindex + 1).line);
                            System.out.println(intersections + "" + a);
                            if(intersections.size() > 0){
                                intersections.retainAll(a);
                            }
                            else{
                                intersections.addAll(a);
                            }
                        }
                    }
                    active.remove(pindex);
                } else {
                    p.line.added = true;
                    int pindex = Collections.binarySearch(active, p, new compY());
                    if(pindex >= 0){
                        System.out.println("error");
                    }
                    pindex = -(pindex + 1);
                    active.add(pindex, p);
                    if(pindex > 0 && active.get(pindex - 1).line.intersects(active.get(pindex).line)){
                        ArrayList<Line> a = new ArrayList<>();
                            a.add(active.get(pindex - 1).line);
                            a.add(active.get(pindex).line);
                            System.out.println(intersections + "" + a);
                            if(intersections.size() > 0){
                                intersections.retainAll(a);
                            }
                            else{
                                intersections.addAll(a);
                            }
                    }
                    if(pindex < active.size() - 1 && active.get(pindex).line.intersects(active.get(pindex + 1).line)){
                        ArrayList<Line> a = new ArrayList<>();
                            a.add(active.get(pindex).line);
                            a.add(active.get(pindex + 1).line);
                            System.out.println(intersections + "" + a);
                            if(intersections.size() > 0){
                                intersections.retainAll(a);
                            }
                            else{
                                intersections.addAll(a);
                            }
                    }
                }
                index++;
            }
            index++;
        }
        System.out.println(intersections);

        in.close();
        // out.close();
    }

    public static class compX implements Comparator<Point> {
        @Override
        public int compare(cowjump.Point o1, cowjump.Point o2) {
            if (o1.x - o2.x == 0) {
                return o1.y - o2.y;
            }
            return o1.x - o2.x;
        }
    }

    public static class compY implements Comparator<Point> {
        @Override
        public int compare(cowjump.Point o1, cowjump.Point o2) {
            if (o1.y - o2.y == 0) {
                return o1.x - o2.x;
            }
            return o1.y - o2.y;
        }
    }

    public static class Point {
        int x;
        int y;
        Line line;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
        @Override
        public boolean equals(Object obj) {
            Point p = (Point) obj;
            return p.x == x && p.y == y;
        }
        @Override
        public String toString() {
            return x + " " + y;
        }
    }

    public static class Line {
        int index;
        Point p1;
        Point p2;
        float slope;
        boolean added = false;

        public Line(Point p1, Point p2, int index) {
            this.p1 = p1;
            this.p2 = p2;
            this.slope = ((float) p1.y - (float) p2.y) / ((float) p1.x - (float) p2.x);
            this.index = index;
        }

        public boolean intersects(Line l) {
            float slope1 = ((float) p1.y - (float) l.p1.y) / ((float) p1.x - (float) l.p1.x);
            float slope2 = ((float) p2.y - (float) l.p1.y) / ((float) p2.x - (float) l.p1.x);
            if ((l.slope >= slope1 && l.slope <= slope2) || (l.slope >= slope1 && l.slope <= slope2)) {
                return true;
            }
            return false;
        }
        @Override
        public String toString() {
            return (index + 1) + "";
        }
    }
}