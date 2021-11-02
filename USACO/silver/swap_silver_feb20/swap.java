/*
ID: ssk49881
LANG: JAVA
TASK: swap
*/

import java.io.*;
import java.util.*;

public class swap {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("swap.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("swap.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numSwaps = Integer.parseInt(tokenizer.nextToken());
        int numTimes = Integer.parseInt(tokenizer.nextToken());
        int[] swap1 = new int[numSwaps];
        int[] swap2 = new int[numSwaps];
        for (int i = 0; i < numSwaps; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            swap1[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
            swap2[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
        }
        int[] after = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            int point = i;
            for (int j = 0; j < numSwaps; j++) {
                if (point >= swap1[j] && point <= swap2[j]) {
                    point = swap2[j] - (point - swap1[j]);
                }
            }
            after[i] = point;
        }
        int[] cycleNum = new int[numCows];
        int[] cycleI = new int[numCows];
        Arrays.fill(cycleNum, -1);
        ArrayList<ArrayList<Integer>> cycles = new ArrayList<>();
        int[] answer = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            if (cycleNum[i] == -1) {
                cycles.add(new ArrayList<>());
                int cycleIndex = cycles.size() - 1;
                ArrayList<Integer> cycle = cycles.get(cycleIndex);
                int last = i;
                while (!cycle.contains(last)) {
                    cycle.add(last);
                    cycleNum[last] = cycleIndex;
                    cycleI[last] = cycle.size() - 1;
                    last = after[last];
                }
            }
            ArrayList<Integer> cycle = cycles.get(cycleNum[i]);
            answer[cycle.get((cycleI[i] + numTimes) % cycle.size())] = i;
        }
        for (int i : answer) {
            out.println(i + 1);
        }

        in.close();
        out.close();
    }
}