/*
ID: ssk49881
LANG: JAVA
TASK: where
*/

import java.io.*;
import java.util.*;

public class where {
    public static int dim;
    public static int[][] pic;
    public static int[][] component;
    public static ArrayList<Integer>[][] neighbor;
    public static int numComponents = 0;
    public static int numSolutions = 0;
    public static boolean[][][][] test;
    public static int[] componentsPer = new int[26];

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("where.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("where.out")));
        dim = Integer.parseInt(in.readLine());
        pic = new int[dim][dim];
        component = new int[dim][dim];
        neighbor = new ArrayList[dim][dim];
        for (int i = 0; i < dim; i++) {
            String s = in.readLine();
            for (int j = 0; j < dim; j++) {
                pic[i][j] = s.charAt(j) - 'A';
                neighbor[i][j] = new ArrayList<>();
            }
        }
        test = new boolean[dim][dim][dim][dim];
        for (boolean[][][] i : test) {
            for (boolean[][] j : i) {
                for (boolean[] k : j) {
                    Arrays.fill(k, true);
                }
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (i > 0 && pic[i - 1][j] == pic[i][j]) {
                    neighbor[i][j].add((i - 1) * dim + j);
                }
                if (j > 0 && pic[i][j - 1] == pic[i][j]) {
                    neighbor[i][j].add(i * dim + (j - 1));
                }
                if (i < dim - 1 && pic[i + 1][j] == pic[i][j]) {
                    neighbor[i][j].add((i + 1) * dim + j);
                }
                if (j < dim - 1 && pic[i][j + 1] == pic[i][j]) {
                    neighbor[i][j].add(i * dim + (j + 1));
                }
            }
        }
        for (int height = dim - 1; height >= 0; height--) {
            for (int top = 0; top + height < dim; top++) {
                for (int width = dim - 1; width >= 0; width--) {
                    for (int left = 0; left + width < dim; left++) {
                        int bottom = top + height;
                        int right = left + width;
                        if (!test[top][bottom][left][right]) {
                            continue;
                        }
                        for (int[] i : component) {
                            Arrays.fill(i, -2);
                        }
                        numComponents = 0;
                        Arrays.fill(componentsPer, 0);
                        for (int i = top; i <= bottom; i++) {
                            for (int j = left; j <= right; j++) {
                                if (component[i][j] == -2) {
                                    componentsPer[pic[i][j]]++;
                                    flood_fill(i, j, top, bottom, left, right);
                                    numComponents++;
                                }
                            }
                        }
                        int num1 = 0;
                        int numMul = 0;
                        for (int i : componentsPer) {
                            if (i == 1) {
                                num1++;
                            }
                            if (i > 1) {
                                numMul++;
                            }
                        }
                        if (num1 == 1 && numMul == 1) {
                            numSolutions++;
                            for (int i = top; i <= bottom; i++) {
                                for (int j = i; j <= bottom; j++) {
                                    for (int k = left; k <= right; k++) {
                                        for (int l = k; l <= right; l++) {
                                            test[i][j][k][l] = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        out.println(numSolutions);

        in.close();
        out.close();
    }

    public static void flood_fill(int x, int y, int top, int bottom, int left, int right) {
        ArrayList<Integer> queue = new ArrayList<>();
        queue.add(dim * x + y);
        while (!queue.isEmpty()) {
            int n = queue.remove(0);
            x = n / dim;
            y = n % dim;
            component[x][y] = numComponents;
            for (int num : neighbor[x][y]) {
                int nx = num / dim;
                int ny = num % dim;
                if (top <= nx && nx <= bottom && left <= ny && ny <= right && component[nx][ny] == -2) {
                    queue.add(dim * nx + ny);
                }
            }
        }
    }
}