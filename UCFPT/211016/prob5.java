/*
ID: ssk49881
LANG: JAVA
TASK: prob5
*/

import java.io.*;
import java.util.*;

public class prob5 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            out.println("Triathlon #" + (i + 1));
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numRacers = Integer.parseInt(tokenizer.nextToken());
            int race1 = Integer.parseInt(tokenizer.nextToken());
            int race2 = Integer.parseInt(tokenizer.nextToken());
            int race3 = Integer.parseInt(tokenizer.nextToken());
            Racer[] racers = new Racer[numRacers];
            for (int j = 0; j < numRacers; j++) {
                tokenizer = new StringTokenizer(in.readLine());
                String name = tokenizer.nextToken();
                double s1 = Double.parseDouble(tokenizer.nextToken());
                double s2 = Double.parseDouble(tokenizer.nextToken());
                double s3 = Double.parseDouble(tokenizer.nextToken());
                racers[j] = new Racer(name, s1, s2, s3);
                racers[j].calcTime(race1, race2, race3);
                // System.out.println(racers[j].time);
            }
            Arrays.sort(racers);
            for (int j = 0; j < numRacers; j++) {
                out.println(racers[j].name + " " + racers[j].hours + " hour(s) " + racers[j].minutes + " minute(s) "
                        + racers[j].seconds + " second(s)");
            }
        }
        in.close();
        out.close();
    }
}

class Racer implements Comparable<Racer> {
    double speed1;
    double speed2;
    double speed3;
    String name;
    int seconds;
    int minutes;
    int hours;
    double time;

    public Racer(String name, double speed1, double speed2, double speed3) {
        this.name = name;
        this.speed1 = speed1;
        this.speed2 = speed2;
        this.speed3 = speed3;
    }

    public void calcTime(int race1, int race2, int race3) {
        time = race1 / speed1 + race2 / speed2 + race3 / speed3;
        hours = (int) time / 3600;
        minutes = (int) (time - 3600 * hours) / 60;
        seconds = (int) (time - 3600 * hours - 60 * minutes);
    }

    @Override
    public int compareTo(Racer o) {
        if (this.time - o.time < 0)
            return -1;
        if (this.time - o.time > 0)
            return 1;
        return 0;
    }
}