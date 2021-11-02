/*
ID: ssk49881
LANG: JAVA
TASK: clocktree
*/

import java.io.*;
import java.util.*;

public class clocktree {
    public static int[] time;
    public static ArrayList<Integer>[] neighbors;
    public static boolean[] visited;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("clocktree.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("clocktree.out")));

        int numPoints = Integer.parseInt(in.readLine());
        time = new int[numPoints];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        neighbors = new ArrayList[numPoints];
        visited = new boolean[numPoints];
        for (int i = 0; i < numPoints; i++) {
            time[i] = Integer.parseInt(tokenizer.nextToken());
            neighbors[i] = new ArrayList<>();
        }
        for (int i = 0; i < numPoints - 1; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            neighbors[first].add(second);
            neighbors[second].add(first);
        }
        int solutions = 0;
        for (int i = 0; i < numPoints; i++) {
            visited = new boolean[numPoints];
            int sum = dfs(i, 0, 0);
            // System.out.println(i + " " + (sum % 12 + 12) % 12);
            if ((sum % 12 + 12) % 12 == 0 || (sum % 12 + 12) % 12 == 1) {
                solutions++;
            }
        }
        out.println(solutions);

        in.close();
        out.close();
    }

    public static int dfs(int current, int sum, int depth) {
        sum += (depth % 2 == 0 ? 1 : -1) * time[current];
        visited[current] = true;
        for (int i : neighbors[current]) {
            if (!visited[i]) {
                sum = dfs(i, sum, depth + 1);
            }
        }
        return sum;
    }
}