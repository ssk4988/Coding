/*
ID: ssk49881
LANG: JAVA
TASK: meetings
*/

import java.io.*;
import java.util.*;

public class meetings {
    public static void main(String[] args) throws Exception {
        long start = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("meetings.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("meetings.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int maxNum = Integer.parseInt(tokenizer.nextToken());
        int numMeetings = 0;
        int sumDone = 0;
        int sumWeights = 0;
        cow[] cows = new cow[numCows];
        ArrayList<cow> leftbound = new ArrayList<>();
        ArrayList<cow> rightbound = new ArrayList<>();
        for (int i = 0; i < numCows; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int weight = Integer.parseInt(tokenizer.nextToken());
            int pos = Integer.parseInt(tokenizer.nextToken());
            int dir = Integer.parseInt(tokenizer.nextToken());
            sumWeights += weight;
            cows[i] = new cow(pos, weight, dir, maxNum);
            if (dir == 1) {
                rightbound.add(new cow(pos, weight, dir, maxNum));
            } else {
                leftbound.add(new cow(pos, weight, dir, maxNum));
            }
            // System.out.println(weight + " " + pos + " " + dir);
        }
        Arrays.sort(cows, new CompX());
        Collections.sort(leftbound, new CompX());
        Collections.sort(rightbound, new CompX());
        for (int i = 0; i < leftbound.size(); i++) {
            leftbound.get(i).weight = cows[i].weight;
        }
        for (int i = 0; i < rightbound.size(); i++) {
            rightbound.get(i).weight = cows[leftbound.size() + i].weight;
        }
        cow[] fixedCows = new cow[numCows];
        for (int i = 0; i < leftbound.size(); i++) {
            fixedCows[i] = leftbound.get(i);
        }
        for (int i = 0; i < rightbound.size(); i++) {
            fixedCows[i + leftbound.size()] = rightbound.get(i);
        }
        Arrays.sort(fixedCows, new CompTime());
        int time = 0;
        for (int i = 0; i < fixedCows.length; i++) {
            sumDone += fixedCows[i].weight;
            if (2 * sumDone >= sumWeights) {
                time = fixedCows[i].time;
                break;
            }
        }
        boolean firstTime = true;
        int meetCount = 0;
        int i2 = 0;
        for (int i = 0; i < numCows; i++) {
            if (cows[i].dir != 1) {
                if (!firstTime) {
                    meetCount--;
                }
                continue;
            }
            int pos = cows[i].pos;
            if (firstTime) {
                i2 = i + 1;
                firstTime = false;
            }
            while (i2 < numCows && cows[i2].pos - pos <= 2 * time) {
                if (cows[i2].dir == -1) {
                    meetCount++;
                }
                i2++;
            }
            numMeetings += meetCount;

        }
        // System.out.println(numMeetings + " " + (System.currentTimeMillis() - start));
        out.println(numMeetings);

        in.close();
        out.close();
    }

    public static class CompX implements Comparator<cow> {
        @Override
        public int compare(meetings.cow o1, meetings.cow o2) {
            return o1.pos - o2.pos;
        }
    }

    public static class CompTime implements Comparator<cow> {
        @Override
        public int compare(meetings.cow o1, meetings.cow o2) {
            return o1.time - o2.time;
        }
    }

    public static class cow {
        public int pos;
        public int weight;
        public int dir;
        public int time;

        public cow(int pos, int weight, int dir, int maxNum) {
            this.pos = pos;
            this.weight = weight;
            this.dir = dir;
            if (dir == 1) {
                time = maxNum - pos;
            } else {
                time = pos;
            }
        }
    }
}
