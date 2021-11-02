/*
ID: ssk49881
LANG: JAVA
TASK: perimeter
*/

import java.io.*;
import java.util.*;

public class perimeter {
    public static int numComponents = 0;
    public static int dim;
    public static boolean[][] cream;
    public static int[][] component;
    public static int[][] neighbor;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("perimeter.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("perimeter.out")));

        dim = Integer.parseInt(in.readLine());
        cream = new boolean[dim][dim];
        component = new int[dim][dim];
        neighbor = new int[dim][dim];

        for (int[] i : component) {
            Arrays.fill(i, -3);
        }
        for (int i = 0; i < dim; i++) {
            String str = in.readLine();
            for (int j = 0; j < dim; j++) {
                if (str.charAt(j) == '#') {
                    cream[i][j] = true;
                    component[i][j] = -2;
                }
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (component[i][j] == -2) {
                    flood_fill(i, j);
                    numComponents++;
                }
            }
        }
        int[] areas = new int[numComponents];
        int[] perimeters = new int[numComponents];
        for (int k = 0; k < numComponents; k++) {
            for (int i = 0; i < dim; i++) {
                for (int j = 0; j < dim; j++) {
                    if (component[i][j] == k) {
                        areas[k]++;
                        perimeters[k] += (4 - neighbor[i][j]);
                    }
                }
            }
        }
        int maxArea = 0;
        int minPerimeter = Integer.MAX_VALUE;
        for (int i = 0; i < numComponents; i++) {
            if (areas[i] > maxArea) {
                maxArea = areas[i];
                minPerimeter = perimeters[i];
            } else if (areas[i] == maxArea) {
                minPerimeter = Math.min(minPerimeter, perimeters[i]);
            }
        }
        out.println(maxArea + " " + minPerimeter);

        in.close();
        out.close();
    }

    public static void flood_fill(int i, int j) {
        boolean[][] queued = new boolean[dim][dim];
        ArrayList<Integer> x = new ArrayList<>();
        ArrayList<Integer> y = new ArrayList<>();
        x.add(i);
        y.add(j);
        while (!x.isEmpty()) {
            i = x.remove(0);
            j = y.remove(0);
            if (component[i][j] != -2)
                continue;
            component[i][j] = numComponents;
            if (i > 0) {
                if (component[i - 1][j] != -3) {
                    neighbor[i][j]++;
                }
                if (component[i - 1][j] == -2 && !queued[i - 1][j]) {
                    x.add(i - 1);
                    y.add(j);
                    queued[i - 1][j] = true;
                }
            }
            if (j > 0) {
                if (component[i][j - 1] != -3) {
                    neighbor[i][j]++;
                }
                if (component[i][j - 1] == -2 && !queued[i][j - 1]) {
                    x.add(i);
                    y.add(j - 1);
                    queued[i][j - 1] = true;
                }
            }
            if (i < dim - 1) {
                if (component[i + 1][j] != -3) {
                    neighbor[i][j]++;
                }
                if (component[i + 1][j] == -2 && !queued[i + 1][j]) {
                    x.add(i + 1);
                    y.add(j);
                    queued[i + 1][j] = true;
                }
            }
            if (j < dim - 1) {
                if (component[i][j + 1] != -3) {
                    neighbor[i][j]++;
                }
                if (component[i][j + 1] == -2 && !queued[i][j + 1]) {
                    x.add(i);
                    y.add(j + 1);
                    queued[i][j + 1] = true;
                }
            }
        }
    }
}