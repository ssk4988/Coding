/*
ID: ssk49881
LANG: JAVA
TASK: stall4
*/

import java.io.*;
import java.util.*;

public class stall4 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("stall4.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("stall4.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numStalls = Integer.parseInt(tokenizer.nextToken());
        int[][] pathways = new int[numCows + numStalls + 2][numCows + numStalls + 2];
        int source = numCows + numStalls;
        int sink = numCows + numStalls + 1;

        for (int i = 0; i < numCows; i++) {
            pathways[source][i] = 1;
            tokenizer = new StringTokenizer(in.readLine());
            int stalls = Integer.parseInt(tokenizer.nextToken());
            for(int j = 0; j < stalls; j++){
                int stall = Integer.parseInt(tokenizer.nextToken());
                pathways[i][numCows + stall - 1] = 1;
            }
        }
        for(int i =0; i < numStalls; i++){
            pathways[numCows + i][sink] = 1;
        }
        out.println(maximumMatching(pathways, source, sink));

        in.close();
        out.close();
    }
    public static int maximumMatching(int[][] capacity, int source, int sink) {
        if (source == sink) {
            return Integer.MAX_VALUE;
        }
        int totalflow = 0;
        int[] prevNode = new int[capacity.length];
        int[] flow = new int[capacity.length];
        boolean[] visited = new boolean[capacity.length];
        outer: while (true) {
            Arrays.fill(prevNode, -1);
            Arrays.fill(visited, false);
            Arrays.fill(flow, 0);
            flow[source] = Integer.MAX_VALUE;
            int maxloc = -1;
            inner: while (true) {
                int maxFlow = 0;
                maxloc = -1;
                for (int i = 0; i < capacity.length; i++) {
                    if (flow[i] > maxFlow && !visited[i]) {
                        maxFlow = flow[i];
                        maxloc = i;
                    }
                }
                if (maxloc == -1) {
                    break outer;
                }
                if (maxloc == sink) {
                    break inner;
                }
                visited[maxloc] = true;
                for (int i = 0; i < capacity.length; i++) {
                    if (capacity[maxloc][i] != 0 && flow[i] < Math.min(maxFlow, capacity[maxloc][i])) {
                        prevNode[i] = maxloc;
                        flow[i] = Math.min(maxFlow, capacity[maxloc][i]);
                    }
                }
            }
            int pathcapacity = flow[sink];
            totalflow += pathcapacity;
            System.out.println(totalflow + " " + pathcapacity);

            int curnode = sink;
            int nextNode = prevNode[curnode];
            while (curnode != source) {
                nextNode = prevNode[curnode];
                capacity[nextNode][curnode] -= pathcapacity;
                capacity[curnode][nextNode] += pathcapacity;
                curnode = nextNode;
            }
        }
        return totalflow;
    }
}