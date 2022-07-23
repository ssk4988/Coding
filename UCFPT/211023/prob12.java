/*
ID: ssk49881
LANG: JAVA
TASK: prob12
*/

import java.io.*;
import java.util.*;

public class prob12 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for (int count = 0; count < n; count++) {
            int numPlaces = Integer.parseInt(in.readLine());
            int[] heights = new int[numPlaces];
            for (int i = 0; i < numPlaces; i++) {
                heights[i] = Integer.parseInt(in.readLine());
            }
            boolean[][] adjacent = new boolean[numPlaces][numPlaces];
            int[][] work = new int[numPlaces][numPlaces];
            int numPaths = Integer.parseInt(in.readLine());
            for (int i = 0; i < numPaths; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                int p1 = Integer.parseInt(tokenizer.nextToken().replace("(", "").replace(",", "")) - 1;
                int p2 = Integer.parseInt(tokenizer.nextToken().replace(")", "")) - 1;
                adjacent[p1][p2] = true;
                adjacent[p2][p1] = true;
                work[p1][p2] = Math.abs(heights[p1] - heights[p2]);
                work[p2][p1] = work[p1][p2];
            }
            for (int i = 0; i < numPlaces; i++) {
                for (int j = 0; j < numPlaces; j++) {
                    if (i == j || work[i][j] != 0)
                        continue;
                    work[i][j] = 10000000;
                }
            }
            for (int i = 0; i < numPlaces; i++) {
                for (int j = 0; j < numPlaces; j++) {
                    for (int k = 0; k < numPlaces; k++) {
                        if (work[i][k] + work[k][j] >= 0 && work[i][k] + work[k][j] < work[i][j]) {
                            work[i][j] = work[i][k] + work[k][j];
                        }
                    }
                }
            }
            for (int i = 0; i < numPlaces; i++) {
                // System.out.println(Arrays.toString(work[i]));
            }
            int numPoints = Integer.parseInt(in.readLine());
            int sum = 0;
            int current = 0;
            for (int i = 0; i < numPoints; i++) {
                int p = Integer.parseInt(in.readLine()) - 1;
                sum += work[current][p];
                current = p;
            }
            sum += work[numPlaces - 1][current];
            System.out.println("The least amount of work on trip " + (count + 1) + " is: " + sum);
        }
        in.close();
        out.close();
    }
}