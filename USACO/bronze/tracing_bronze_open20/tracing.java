/*
ID: ssk49881
LANG: JAVA
TASK: tracing
*/

import java.io.*;
import java.util.*;

public class tracing {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("tracing.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("tracing.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numShakes = Integer.parseInt(tokenizer.nextToken());
        boolean[] sick = new boolean[numCows];
        String sickstr = in.readLine();
        int[] tcow1 = new int[251];
        int[] tcow2 = new int[251];
        Arrays.fill(tcow1, -1);
        Arrays.fill(tcow2, -1);
        for (int i = 0; i < numCows; i++) {
            sick[i] = sickstr.charAt(i) == '1' ? true : false;
        }
        for (int i = 0; i < numShakes; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int time = Integer.parseInt(tokenizer.nextToken());
            int cow1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int cow2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            tcow1[time] = cow1;
            tcow2[time] = cow2;
        }
        boolean[] consistent_time = new boolean[252];
        boolean[] consistent_cow = new boolean[numCows];
        int minTime = 255;
        int maxTime = 0;
        for (int k = 0; k < consistent_time.length; k++) {
            for (int origin = 0; origin < numCows; origin++) {
                if (!sick[origin])
                    continue;
                boolean[] alreadysick = new boolean[numCows];
                int[] numhandshakes = new int[numCows];
                alreadysick[origin] = true;
                for (int t = 0; t < 251; t++) {
                    if (tcow1[t] == -1)
                        continue;
                    if(sick[tcow1[t]]) numhandshakes[tcow1[t]]++;
                    if(sick[tcow2[t]]) numhandshakes[tcow2[t]]++;
                    if (numhandshakes[tcow1[t]] <= k && alreadysick[tcow1[t]]) {
                        alreadysick[tcow2[t]] = true;
                    }
                    if (numhandshakes[tcow2[t]] <= k && alreadysick[tcow2[t]]) {
                        alreadysick[tcow1[t]] = true;
                    }
                }
                if (Arrays.equals(alreadysick, sick)) {
                    consistent_cow[origin] = true;
                    consistent_time[k] = true;
                    if (k > maxTime)
                        maxTime = k;
                    if (k < minTime)
                        minTime = k;
                }
            }
        }
        int origins = 0;
        for (int i = 0; i < consistent_cow.length; i++) {
            if (consistent_cow[i])
                origins++;
        }
        if (consistent_time[251]) {
            out.println(origins + " " + minTime + " Infinity");
        } else {
            out.println(origins + " " + minTime + " " + maxTime);
        }

        in.close();
        out.close();
    }
}

class Tuple implements Comparable<Tuple> {
    int time;
    int id;

    public Tuple(int id, int time) {
        this.id = id;
        this.time = time;
    }

    @Override
    public int compareTo(Tuple o) {
        return this.time - o.time;
    }
}