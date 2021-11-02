/*
ID: ssk49881
LANG: JAVA
TASK: convention2
*/

import java.io.*;
import java.util.*;

public class convention2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("convention2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("convention2.out")));
        int numCows = Integer.parseInt(in.readLine());
        cow[] cowsSen = new cow[numCows];
        cow[] cowsArr = new cow[numCows];
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int seniority = i;
            int arrival = Integer.parseInt(tokenizer.nextToken());
            int time = Integer.parseInt(tokenizer.nextToken());
            cow c = new cow(seniority, arrival, time);
            cowsSen[i] = c;
            cowsArr[i] = c;
        }
        Arrays.sort(cowsArr, new CompArr());

        int maxWait = 0;
        cow current;
        ArrayList<cow> queue = new ArrayList<>();
        int index = 1;
        int lasttime = cowsArr[0].arrival;
        queue.add(cowsArr[0]);
        while (index < numCows || !queue.isEmpty()) {
            current = queue.remove(0);
            if (lasttime < current.arrival)
                lasttime = current.arrival;
            int newWait = lasttime - current.arrival;
            if (newWait > maxWait)
                maxWait = newWait;
            lasttime = lasttime + current.time;
            while (index < numCows && (queue.isEmpty() || cowsArr[index].arrival <= lasttime)) {
                int addIndex = Collections.binarySearch(queue, cowsArr[index], new CompSen());
                if (addIndex < 0)
                    addIndex = -(addIndex + 1);
                queue.add(addIndex, cowsArr[index]);
                index++;
            }
        }
        out.println(maxWait);

        in.close();
        out.close();
    }

    public static class CompSen implements Comparator<cow> {
        @Override
        public int compare(convention2.cow o1, convention2.cow o2) {
            if (o1.seniority - o2.seniority == 0)
                return o1.arrival - o2.arrival;
            return o1.seniority - o2.seniority;
        }
    }

    public static class CompArr implements Comparator<cow> {
        @Override
        public int compare(convention2.cow o1, convention2.cow o2) {
            if (o1.arrival - o2.arrival == 0)
                return o1.seniority - o2.seniority;
            return o1.arrival - o2.arrival;
        }
    }

    public static class cow {
        int seniority;
        int arrival;
        int time;

        public cow(int seniority, int arrival, int time) {
            this.seniority = seniority;
            this.arrival = arrival;
            this.time = time;
        }
    }
}