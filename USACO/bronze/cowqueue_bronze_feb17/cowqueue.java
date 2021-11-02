/*
ID: ssk49881
LANG: JAVA
TASK: cowqueue
*/

import java.io.*;
import java.util.*;

public class cowqueue {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cowqueue.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowqueue.out")));
        int numCows = Integer.parseInt(in.readLine());
        ArrayList<Cow> cows = new ArrayList<>();
        for (int i = 0; i < numCows; i++) {
            StringTokenizer c = new StringTokenizer(in.readLine());
            int start = Integer.parseInt(c.nextToken());
            int duration = Integer.parseInt(c.nextToken());
            cows.add(new Cow(start, duration));
        }
        Collections.sort(cows);
        int time = cows.get(0).end;
        for (int i = 1; i < cows.size(); i++) {
            // System.out.println(time + " " + cows.get(i).start + " " +
            // cows.get(i).duration);
            if (cows.get(i).start >= time) {
                time = cows.get(i).end;
            } else {
                time += cows.get(i).duration;
            }

        }
        out.println(time);
        in.close();
        out.close();
    }

    public static class Cow implements Comparable<Cow> {
        public int start;
        public int duration;
        public int end;

        public Cow(int start, int duration) {
            this.start = start;
            this.duration = duration;
            this.end = this.start + this.duration;
        }

        @Override
        public int compareTo(cowqueue.Cow o) {
            return this.start - o.start;
        }
    }
}
