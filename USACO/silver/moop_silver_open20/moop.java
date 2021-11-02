/*
ID: ssk49881
LANG: JAVA
TASK: moop
*/

import java.io.*;
import java.util.*;

public class moop {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("moop.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("moop.out")));
        int numPoints = Integer.parseInt(in.readLine());
        Point[] points = new Point[numPoints];
        ArrayList<Component> components = new ArrayList<>();
        for(int i = 0; i < numPoints; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            points[i] = new Point(x, y);
        }
        Arrays.sort(points);
        for(int i = 0; i < numPoints; i++){
            components.add(new Component(points[i]));
        }
        boolean revise = true;
        while(revise){
            revise = false;
            int i = 0;
            while(i < components.size() - 1){
                Component comp1 = components.get(i);
                Component comp2 = components.get(i + 1);
                if(comp1.minX <= comp2.maxX){
                    comp1.merge(comp2);
                    components.remove(i + 1);
                    revise = true;
                }
                else{
                    i++;
                }
            }
        }
        out.println(components.size());
        /*for(Component c : components){
            for(Point p : c.points){
                System.out.println(p.x + " " + p.y);
            }
            System.out.println("min: " + c.minX + " max: " + c.maxX);
            System.out.println();
        }*/


        in.close();
        out.close();
    }

    public static class Point implements Comparable<Point> {
        int x;
        int y;
        public Point(int x, int y){
            this.x = x;
            this.y = y;
        }
        @Override
        public int compareTo(moop.Point o) {
            if(this.y == o.y){
                return this.x - o.x;
            }
            return this.y - o.y;
        }
    }

    public static class Component {
        ArrayList<Point> points = new ArrayList<>();
        int maxX = -1;
        int minX = -1;

        public Component(Point p){
            points.add(p);
            this.maxX = p.x;
            this.minX = p.x;
        }

        public void merge(Component c){
            for(Point p : c.points){
                points.add(p);
                if(maxX < p.x) maxX = p.x;
                if(minX > p.x) minX = p.x;
            }
        }
    }
}