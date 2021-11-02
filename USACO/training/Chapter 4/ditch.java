/*
ID: ssk49881
LANG: JAVA
TASK: ditch
*/

import java.io.*;
import java.util.*;

public class ditch {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("ditch.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ditch.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numDitches = Integer.parseInt(tokenizer.nextToken());
        int numIntersections = Integer.parseInt(tokenizer.nextToken());

        int[][] capacity = new int[numIntersections][numIntersections];
        for (int i = 0; i < numDitches; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            capacity[Integer.parseInt(tokenizer.nextToken()) - 1][Integer.parseInt(tokenizer.nextToken())
                    - 1] += Integer.parseInt(tokenizer.nextToken());
        }
        out.println(networkFlow(capacity, 0, numIntersections - 1));

        in.close();
        out.close();
    }

    public static int networkFlow(int[][] capacity, int source, int sink) {
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