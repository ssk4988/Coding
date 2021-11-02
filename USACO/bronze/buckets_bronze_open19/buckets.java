/*
ID: ssk49881
LANG: JAVA
TASK: buckets
*/

import java.io.*;
import java.util.*;

public class buckets {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("buckets.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("buckets.out")));

        int[][] distTo = new int[10][10];
        for (int[] d : distTo) {
            Arrays.fill(d, Integer.MAX_VALUE);
        }
        int barnX = 0, barnY = 0, rockX = 0, rockY = 0, lakeX = 0, lakeY = 0;
        for (int i = 0; i < 10; i++) {
            String input = in.readLine();
            for (int j = 0; j < 10; j++) {
                if (input.charAt(j) == 'B') {
                    barnY = i;
                    barnX = j;
                }
                if (input.charAt(j) == 'R') {
                    rockY = i;
                    rockX = j;
                }
                if (input.charAt(j) == 'L') {
                    lakeY = i;
                    lakeX = j;
                }
            }
        }
        distTo[lakeX][lakeY] = 0;
        for (int dist = 0; dist < 21; dist++) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (distTo[i][j] != dist) {
                        continue;
                    }
                    if (i == rockX && j == rockY) {
                        continue;
                    }
                    if (i != 0 && dist + 1 < distTo[i - 1][j]) {
                        distTo[i - 1][j] = dist + 1;
                    }
                    if (j != 0 && dist + 1 < distTo[i][j - 1]) {
                        distTo[i][j - 1] = dist + 1;
                    }
                    if (i != 9 && dist + 1 < distTo[i + 1][j]) {
                        distTo[i + 1][j] = dist + 1;
                    }
                    if (j != 9 && dist + 1 < distTo[i][j + 1]) {
                        distTo[i][j + 1] = dist + 1;
                    }
                }
            }
        }
        out.println(distTo[barnX][barnY] - 1);

        in.close();
        out.close();
    }
}