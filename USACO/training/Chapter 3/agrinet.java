/*
ID: ssk49881
LANG: JAVA
TASK: agrinet
*/

import java.io.*;
import java.util.*;

public class agrinet {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("agrinet.in"));
        PrintWriter out = new PrintWriter(new File("agrinet.out"));
        int numFarms = Integer.parseInt(in.nextLine());
        int totalDist = 0;
        int[][] weights = new int[numFarms][numFarms];
        int[] distances = new int[numFarms];
        int[] source = new int[numFarms]; // index of source node for spanning tree
        boolean[] inTree = new boolean[numFarms];
        for (int i = 0; i < numFarms; i++) {
            String phrase = in.nextLine();
            while (phrase.split(" ").length < numFarms) {
                phrase += " " + in.nextLine();
            }
            //System.out.println("length: " + phrase.split(" ").length);
            for (int j = 0; j < numFarms; j++) {
                weights[i][j] = Integer.parseInt(phrase.split(" ")[j]);
                //System.out.print(weights[i][j] + " ");
            }
            //System.out.println();
        }
        Arrays.fill(distances, Integer.MAX_VALUE);
        Arrays.fill(source, -1);
        distances[0] = 0;
        while (trueCounts(inTree) < numFarms) {
            int minDist = Integer.MAX_VALUE;
            int minDistIndex = 0;
            for (int i = 0; i < numFarms; i++) {
                if (distances[i] < minDist && !inTree[i]) {
                    minDist = distances[i];
                    minDistIndex = i;
                }
            }
            System.out.println(minDistIndex + " added to tree");
            inTree[minDistIndex] = true;
            totalDist += distances[minDistIndex];
            for (int i = 0; i < numFarms; i++) {
                if (weights[minDistIndex][i] < distances[i]) {
                    distances[i] = weights[minDistIndex][i];
                    source[i] = minDistIndex;
                }
            }

        }

        out.println(totalDist);

        in.close();
        out.close();
    }

    public static int trueCounts(boolean[] arr) {
        int i = 0;
        for (int j = 0; j < arr.length; j++) {
            if (arr[j]) {
                i++;
            }
        }
        return i;
    }
}