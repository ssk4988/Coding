/*
ID: ssk49881
LANG: JAVA
TASK: fenceplan
*/

import java.io.*;
import java.util.*;

public class fenceplan {
    public static Cow[] cows;
    public static int numCows;
    public static int numComponents = 0;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("fenceplan.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fenceplan.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numCows = Integer.parseInt(tokenizer.nextToken());
        int numConnect = Integer.parseInt(tokenizer.nextToken());
        cows = new Cow[numCows];
        for (int i = 0; i < numCows; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            cows[i] = new Cow(x, y);
        }
        for (int i = 0; i < numConnect; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken()) - 1;
            int y = Integer.parseInt(tokenizer.nextToken()) - 1;
            cows[x].neighbors.add(cows[y]);
            cows[y].neighbors.add(cows[x]);
        }
        for (int i = 0; i < numCows; i++) {
            if (cows[i].component == -2) {
                cows[i].component = -1;
                flood_fill(cows[i]);
                numComponents++;
            }
        }
        int[][][] bounds = new int[numComponents][2][2];
        for (int i = 0; i < numComponents; i++) {
            bounds[i][0][0] = Integer.MAX_VALUE;
            bounds[i][0][1] = Integer.MIN_VALUE;
            bounds[i][1][0] = Integer.MAX_VALUE;
            bounds[i][1][1] = Integer.MIN_VALUE;
        }
        for (int i = 0; i < numCows; i++) {
            bounds[cows[i].component][0][0] = Math.min(bounds[cows[i].component][0][0], cows[i].x);
            bounds[cows[i].component][0][1] = Math.max(bounds[cows[i].component][0][1], cows[i].x);
            bounds[cows[i].component][1][0] = Math.min(bounds[cows[i].component][1][0], cows[i].y);
            bounds[cows[i].component][1][1] = Math.max(bounds[cows[i].component][1][1], cows[i].y);
        }
        int minPerimeter = Integer.MAX_VALUE;
        for (int i = 0; i < numComponents; i++) {
            int perimeter = 2
                    * (Math.abs(bounds[i][0][0] - bounds[i][0][1]) + Math.abs(bounds[i][1][0] - bounds[i][1][1]));
            // System.out.println(i + " " + perimeter + " " + bounds[i][0][0] + " " +
            // bounds[i][0][1] + " " + bounds[i][1][0] + " " + bounds[i][1][1]);
            minPerimeter = Math.min(perimeter, minPerimeter);
        }
        out.println(minPerimeter);

        in.close();
        out.close();
    }

    public static void flood_fill(Cow c) {
        List<Cow> queue = new ArrayList<>();
        queue.add(c);
        while (!queue.isEmpty()) {
            Cow x = queue.remove(0);
            if (x.component == -1) {
                x.component = numComponents;
                for (Cow j : x.neighbors) {
                    if (j.component == -2) {
                        j.component = -1;
                        queue.add(j);
                    }
                }
            }
        }
        // System.out.println(numComponents);
    }

    public static class Cow {
        int x;
        int y;
        int component = -2;
        List<Cow> neighbors = new ArrayList<>();

        public Cow(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}