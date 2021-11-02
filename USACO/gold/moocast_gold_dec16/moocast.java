/*
ID: ssk49881
LANG: JAVA
TASK: moocast
*/

import java.io.*;
import java.util.*;

public class moocast {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("moocast.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("moocast.out")));
        int numCows = Integer.parseInt(in.readLine());
        Radar[] cows = new Radar[numCows];
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            cows[i] = new Radar(x, y);
        }
        int treesize = 1;
        cows[0].inTree = true;
        cows[0].distance = 0;
        for (int i = 1; i < numCows; i++) {
            cows[i].distance = distance(cows[0], cows[i]);
            cows[i].source = 0;
        }
        while (treesize < numCows) {
            int mindist = Integer.MAX_VALUE;
            int minIndex = -1;
            for (int i = 0; i < numCows; i++) {
                if (!cows[i].inTree && cows[i].distance < mindist) {
                    minIndex = i;
                    mindist = cows[i].distance;
                }
            }
            cows[minIndex].inTree = true;
            treesize++;
            for (int i = 0; i < numCows; i++) {
                if (cows[i].inTree) {
                    continue;
                }
                cows[i].distance = Math.min(cows[i].distance, distance(cows[minIndex], cows[i]));
            }
        }
        int minDist = Integer.MIN_VALUE;
        for (int i = 0; i < numCows; i++) {
            minDist = Math.max(minDist, cows[i].distance);
        }
        out.println(minDist);

        in.close();
        out.close();
    }

    public static int distance(Radar cow1, Radar cow2) {
        return Math.abs(cow1.x - cow2.x) * Math.abs(cow1.x - cow2.x)
                + Math.abs(cow1.y - cow2.y) * Math.abs(cow1.y - cow2.y);
    }

    public static class Radar {
        int x;
        int y;
        int distance = Integer.MAX_VALUE;
        int source = -1;
        boolean inTree = false;

        public Radar(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}