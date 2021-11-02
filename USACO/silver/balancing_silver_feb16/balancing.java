/*
ID: ssk49881
LANG: JAVA
TASK: balancing
*/

import java.io.*;
import java.util.*;

public class balancing {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("balancing.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("balancing.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numPoints = Integer.parseInt(tokenizer.nextToken());

        int[] xval = new int[numPoints];
        int[] yval = new int[numPoints];
        ArrayList<Integer> xset = new ArrayList<>();
        ArrayList<Integer> yset = new ArrayList<>();
        for (int i = 0; i < numPoints; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if (!xset.contains(x))
                xset.add(x);
            if (!yset.contains(y))
                yset.add(y);
            xval[i] = x;
            yval[i] = y;
        }
        Collections.sort(xset);
        Collections.sort(yset);
        for (int i = 0; i < numPoints; i++) {
            xval[i] = xset.indexOf(xval[i]);
            yval[i] = yset.indexOf(yval[i]);
        }
        Point[] data = new Point[numPoints];
        for (int i = 0; i < numPoints; i++) {
            data[i] = new Point(xval[i], yval[i]);
        }
        int minval = Integer.MAX_VALUE;
        Arrays.sort(data);
        for (int xbound = 0; xbound < xset.size(); xbound++) {
            ArrayList<Point> left = new ArrayList<>();
            ArrayList<Point> right = new ArrayList<>();
            for (int i = 0; i < numPoints; i++) {
                if (data[i].x < xbound) {
                    left.add(data[i]);
                } else {
                    right.add(data[i]);
                }
            }
            int leftind = 0;
            int rightind = 0;
            while(leftind < left.size() || rightind < right.size()){
                int yborder = Integer.MAX_VALUE;
                if(leftind < left.size()){
                    yborder = Math.min(yborder, left.get(leftind).y);
                }
                if(rightind < right.size()){
                    yborder = Math.min(yborder, right.get(rightind).y);
                }
                while(leftind < left.size() && left.get(leftind).y == yborder){
                    leftind++;
                }
                while(rightind < right.size() && right.get(rightind).y == yborder){
                    rightind++;
                }
                minval = Math.min(minval, Math.max(Math.max(rightind, right.size() - rightind), Math.max(leftind, left.size() - leftind)));
            }
        }
        out.println(minval);

        in.close();
        out.close();
    }
}

class Point implements Comparable<Point> {
    int x, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(Point o) {
        return this.y - o.y;
    }
}