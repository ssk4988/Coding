/*
ID: ssk49881
LANG: JAVA
TASK: j
*/

import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int pathLength = Integer.parseInt(in.readLine());
        Map<Integer, Integer> rewrite = new HashMap<>();
        int numUniquePoints = 0;
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] pathsequence = new int[pathLength];
        for (int i = 0; i < pathLength; i++) {
            int t = Integer.parseInt(tokenizer.nextToken());
            if (!rewrite.containsKey(t)) {
                rewrite.put(t, numUniquePoints);
                numUniquePoints++;
            }
            int t2 = rewrite.get(t);
            pathsequence[i] = t2;
        }
        int numStations = Integer.parseInt(in.readLine());
        int[] stations = new int[numStations];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numStations; i++) {
            int t = Integer.parseInt(tokenizer.nextToken());
            if (!rewrite.containsKey(t)) {
                rewrite.put(t, numUniquePoints);
                numUniquePoints++;
            }
            int t2 = rewrite.get(t);
            stations[i] = t2;
        }
        ArrayList<Integer>[] locations = new ArrayList[numUniquePoints];
        for (int i = 0; i < numUniquePoints; i++) {
            locations[i] = new ArrayList<>();
        }
        int maxSameTypes = 0;
        for (int i = 0; i < numStations; i++) {
            locations[stations[i]].add(i);
        }
        for (int i = 0; i < locations.length; i++) {
            maxSameTypes = Math.max(maxSameTypes, locations[i].size());
        }
        double[] lengths = new double[numStations / 2 + 1];
        for (int i = 0; i < lengths.length; i++) {
            lengths[i] = Math.sqrt(2 - 2 * Math.cos(2 * Math.PI * i / numStations));
        }
        double[][][][] distances = new double[pathLength][pathLength][maxSameTypes][maxSameTypes];
        for (int i = 0; i < distances.length; i++) {
            for (int j = i; j < distances[i].length; j++) {
                for (int k = 0; k < locations[stations[i]].size(); k++) {
                    for (int l = 0; l < locations[stations[j]].size(); l++) {
                        distances[i][j][k][l] = 10000;
                    }
                }
            }
        }
        for (int pathlen = 0; pathlen < distances.length; pathlen++) {
            for (int pathstart = 0; pathstart + pathlen < distances.length; pathstart++) {
                for (int k = 0; k < locations[stations[pathstart]].size(); k++) {
                    for (int l = 0; l < locations[stations[pathstart + pathlen]].size(); l++) {
                        
                    }
                }
            }
        }
        // System.out.println(Arrays.toString(distances));

        in.close();
        out.close();
    }

    public static class Pair {
        int currentStation;
        double distance;

        public Pair(int currentStation, double distance) {
            this.currentStation = currentStation;
            this.distance = distance;
        }
    }
}