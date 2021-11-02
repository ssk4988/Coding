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
            int radius = Integer.parseInt(tokenizer.nextToken());
            cows[i] = new Radar(x, y, radius);
        }
        for (int i = 0; i < numCows; i++) {
            for (int j = 0; j < numCows; j++) {
                if (i == j) {
                    continue;
                }
                if (cows[i].radius >= Math.pow(Math.abs(cows[i].x - cows[j].x), 2)
                        + Math.pow(Math.abs(cows[i].y - cows[j].y), 2)) {
                    cows[i].neighbors.add(cows[j]);
                }
            }
        }
        int maxReach = 0;
        for (int i = 0; i < numCows; i++) {
            List<Radar> seen = new ArrayList<>();
            List<Radar> queue = new ArrayList<>();
            queue.add(cows[i]);
            while (!queue.isEmpty()) {
                Radar r = queue.remove(0);
                for (Radar n : r.neighbors) {
                    if (!seen.contains(n) && !queue.contains(n)) {
                        queue.add(n);
                    }
                }
                seen.add(r);
            }
            if (seen.size() > maxReach) {
                maxReach = seen.size();
            }
        }
        out.println(maxReach);

        in.close();
        out.close();
    }

    public static class Radar {
        int x;
        int y;
        int radius;
        ArrayList<Radar> neighbors = new ArrayList<>();

        public Radar(int x, int y, int radius) {
            this.x = x;
            this.y = y;
            this.radius = radius * radius;
        }
    }
}