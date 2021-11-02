/*
ID: ssk49881
LANG: JAVA
TASK: lifeguards
*/

import java.io.*;
import java.util.*;

public class lifeguards {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("lifeguards.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lifeguards.out")));
        int numGuards = Integer.parseInt(in.readLine());
        Tuple[] data = new Tuple[2 * numGuards];
        for (int i = 0; i < numGuards; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int start = Integer.parseInt(tokenizer.nextToken());
            int end = Integer.parseInt(tokenizer.nextToken());
            data[2 * i] = new Tuple(start, i);
            data[2 * i + 1] = new Tuple(end, i);
        }
        Arrays.sort(data);
        int[] aloneTime = new int[numGuards];
        int recentTime = 0;
        int totalTime = 0;
        TreeSet<Integer> currentlyOn = new TreeSet<>();
        for (Tuple t : data) {
            if (currentlyOn.size() == 1) {
                aloneTime[currentlyOn.first()] += t.time - recentTime;
            }
            if (currentlyOn.size() != 0) {
                totalTime += t.time - recentTime;
            }
            if (currentlyOn.contains(t.index)) {
                currentlyOn.remove(t.index);
            } else {
                currentlyOn.add(t.index);
            }
            recentTime = t.time;
        }
        int maxTime = 0;
        for (Tuple t : data) {
            maxTime = Math.max(maxTime, totalTime - aloneTime[t.index]);
        }
        out.println(maxTime);

        in.close();
        out.close();
    }

    public static class Tuple implements Comparable<Tuple> {
        int index;
        int time;

        public Tuple(int time, int index) {
            this.time = time;
            this.index = index;
        }

        @Override
        public int compareTo(lifeguards.Tuple o) {
            return this.time - o.time;
        }
    }
}