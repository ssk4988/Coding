/*
ID: ssk49881
LANG: JAVA
TASK: wormsort
*/

import java.io.*;
import java.util.*;

public class wormsort {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("wormsort.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numRoutes = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        int[] location = new int[numCows];
        int[] destination = new int[numCows];
        Cow[] cows = new Cow[numCows];
        int maxW = 0;
        for (int i = 0; i < numCows; i++) {
            int j = Integer.parseInt(tokenizer.nextToken()) - 1;
            destination[j] = i;
            location[i] = j;
            cows[i] = new Cow(i, j);
        }
        for (int i = 0; i < numRoutes; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int weight = Integer.parseInt(tokenizer.nextToken());
            maxW = Math.max(maxW, weight);
            cows[first].neighbors.add(second);
            cows[first].weights.add(weight);
            cows[second].neighbors.add(first);
            cows[second].weights.add(weight);
        }
        int low = 0;
        int high = maxW + 1;
        int mid;
        int numComponents = 0;
        while (low < high) {
            mid = (low + high + 1) / 2;
            for (Cow cow : cows) {
                cow.component = -1;
            }
            boolean condition = true;
            ArrayDeque<Integer> queue = new ArrayDeque<>();
            for (int i = 0; i < numCows; i++) {
                if (cows[i].component == -1) {
                    queue.add(i);
                    while (!queue.isEmpty()) {
                        int index = queue.poll();
                        if (cows[index].component != -1)
                            continue;
                        cows[index].component = numComponents;
                        for (int j = 0; j < cows[index].neighbors.size(); j++) {
                            if (cows[cows[index].neighbors.get(j)].component == -1
                                    && cows[index].weights.get(j) >= mid) {
                                queue.add(cows[index].neighbors.get(j));
                            }
                        }
                    }
                    numComponents++;
                }
            }
            for (int i = 0; i < numCows; i++) {
                if (cows[i].component != cows[cows[i].destination].component) {
                    condition = false;
                    break;
                }
            }
            if (condition) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        int answer = low;
        if (answer == maxW + 1) {
            answer = -1;
        }
        out.println(answer);

        in.close();
        out.close();
    }

    public static class Cow {
        int location;
        int destination;
        int component;
        ArrayList<Integer> neighbors = new ArrayList<>();
        ArrayList<Integer> weights = new ArrayList<>();

        public Cow(int location, int destination) {
            this.location = location;
            this.destination = destination;
            component = -1;
        }
    }
}