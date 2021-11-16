/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numPoints = Integer.parseInt(tokenizer.nextToken());
        int numSlopes = Integer.parseInt(tokenizer.nextToken());
        Point[] points = new Point[numPoints];
        for (int i = 0; i < numPoints; i++) {
            points[i] = new Point(i);
        }
        for (int i = 0; i < numSlopes; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int weight = Integer.parseInt(tokenizer.nextToken());
            points[first].children.add(points[second]);
            points[first].cweights.add(weight);
            points[second].parents.add(points[first]);
            points[second].pweights.add(weight);
        }
        int a = 0;
        for (int i = 0; i < numPoints; i++) {
            if (points[i].parents.size() == 0) {
                a = Math.max(a, dfs(0, points[i]));
            }
        }
        System.out.println(a);

        in.close();
        out.close();
    }

    public static int dfs(int sum, Point p) {
        int answer = 0;
        if (p.memo == -1) {
            for (int i = 0; i < p.children.size(); i++) {
                answer = Math.max(answer, dfs(p.cweights.get(i), p.children.get(i)));
            }
            p.memo = answer;
        }

        return p.memo + sum;
    }

    public static class Point {
        int id;
        int memo = -1;
        ArrayList<Integer> cweights = new ArrayList<>();
        ArrayList<Integer> pweights = new ArrayList<>();
        ArrayList<Point> children = new ArrayList<>();
        ArrayList<Point> parents = new ArrayList<>();

        public Point(int id) {
            this.id = id;
        }
    }
}