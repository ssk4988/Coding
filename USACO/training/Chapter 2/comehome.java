/*
ID: ssk49881
LANG: JAVA
TASK: comehome
*/

import java.io.*;
import java.util.*;

public class comehome {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("comehome.in"));
        PrintWriter out = new PrintWriter(new File("comehome.out"));
        int numPaths = Integer.parseInt(in.nextLine());
        int[][] distances = new int[52][52];
        boolean[][] adjacent = new boolean[52][52];
        for (int[] d : distances) {
            Arrays.fill(d, Integer.MAX_VALUE);
        }
        for (int i = 0; i < numPaths; i++) {
            String phrase = in.nextLine();
            char barn1 = phrase.split(" ")[0].charAt(0);
            char barn2 = phrase.split(" ")[1].charAt(0);
            int dist = Integer.parseInt(phrase.split(" ")[2]);
            int index1, index2;

            if (barn1 - 'a' >= 0) {
                index1 = barn1 - 'a';
            } else {
                index1 = barn1 - 'A' + 26;
            }
            if (barn2 - 'a' >= 0) {
                index2 = barn2 - 'a';
            } else {
                index2 = barn2 - 'A' + 26;
            }
            adjacent[index1][index2] = true;
            adjacent[index2][index1] = true;
            distances[index1][index2] = Math.min(dist, distances[index1][index2]);
            distances[index2][index1] = Math.min(dist, distances[index2][index1]);
        }
        for (int i = 0; i < distances.length; i++) {
            for (int j = 0; j < distances.length; j++) {
                if (!adjacent[i][j]) {
                    distances[i][j] = 100000000;
                }
            }
        }
        for (int k = 0; k < distances.length; k++) {
            for (int i = 0; i < distances.length; i++) {
                for (int j = 0; j < distances.length; j++) {
                    if (distances[i][k] + distances[k][j] < distances[i][j]) {
                        distances[i][j] = distances[i][k] + distances[k][j];
                    }
                }
            }
        }
        char smallest = ' ';
        int shortestPath = Integer.MAX_VALUE;
        for (int i = 26; i < 51; i++) {
            if (distances[i][51] < shortestPath) {
                shortestPath = distances[i][51];
                smallest = (char) ((i - 26) + 'A');
            }
        }
        out.println(smallest + " " + shortestPath);

        in.close();
        out.close();
    }
}