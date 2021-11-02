/*
ID: ssk49881
LANG: JAVA
TASK: fence6
*/

import java.io.*;
import java.util.*;

public class fence6 {
    public static int numFences;
    public static Fence[] fences;
    public static boolean[][] visited;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("fence6.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence6.out")));

        numFences = Integer.parseInt(in.readLine());
        fences = new Fence[numFences + 1];
        for (int i = 1; i < fences.length; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            fences[i] = new Fence(Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()));
            int len1 = Integer.parseInt(tokenizer.nextToken());
            StringTokenizer tokenizer2 = new StringTokenizer(in.readLine());
            for (int j = 0; j < len1; j++) {
                fences[i].sets[0].add(Integer.parseInt(tokenizer2.nextToken()));
            }
            int len2 = Integer.parseInt(tokenizer.nextToken());
            StringTokenizer tokenizer3 = new StringTokenizer(in.readLine());
            for (int j = 0; j < len2; j++) {
                fences[i].sets[1].add(Integer.parseInt(tokenizer3.nextToken()));
            }
        }
        visited = new boolean[numFences + 1][2];
        int minPerimeter = Integer.MAX_VALUE;
        for (int i = 1; i < fences.length; i++) {
            for (int j = 0; j <= 1; j++) {
                visited[i][j] = true;
                int perimeter = dfs(i, i, fences[i].length, minPerimeter);
                if (perimeter < minPerimeter) {
                    minPerimeter = perimeter;
                }
                visited[i][j] = false;
            }
        }
        out.println(minPerimeter);

        in.close();
        out.close();
    }

    public static int dfs(int start, int fenceNum, int value, int max) {
        if (value >= max)
            return max;

        if (fenceNum == start && visited[fenceNum][0] && visited[fenceNum][1]) {
            return value;
        }

        // dir: one of the ends of the line, zero or one.
        for (int dir = 0; dir <= 1; dir++) {
            boolean go = (fenceNum != start) ? !visited[fenceNum][dir] : visited[fenceNum][dir];

            if (go) {
                visited[fenceNum][dir] = true;
                Set<Integer> neighbors = fences[fenceNum].sets[dir];

                for (int neighbor : neighbors) {
                    int neighborDir = fences[neighbor].sets[0].contains(fenceNum) ? 0 : 1;
                    if (!visited[neighbor][neighborDir]) {
                        visited[neighbor][neighborDir] = true;

                        int length = (neighbor != start) ? value + fences[neighbor].length : value;
                        int localResult = dfs(start, neighbor, length, max);
                        max = Math.min(max, localResult);

                        visited[neighbor][neighborDir] = false;
                    }
                }

                visited[fenceNum][dir] = false;
            }
        }

        return max;
    }

    public static class Fence {
        public int length;
        public int id;
        public Set<Integer>[] sets = new Set[2];

        public Fence(int id, int length) {
            this.id = id;
            this.length = length;
            sets[0] = new HashSet<Integer>();
            sets[1] = new HashSet<Integer>();
        }
    }
}