/*
ID: ssk49881
LANG: JAVA
TASK: maze1
*/

import java.io.*;
import java.util.*;

public class maze1 {
    public static void main(String[] args) throws Exception {
        long startTime = System.currentTimeMillis();
        Scanner in = new Scanner(new File("maze1.in"));
        PrintWriter out = new PrintWriter(new File("maze1.out"));

        String phrase = in.nextLine();
        int width = Integer.parseInt(phrase.split(" ")[0]);
        int height = Integer.parseInt(phrase.split(" ")[1]);
        char[][] input = new char[2 * height + 1][2 * width + 1];
        ArrayList<Integer>[][] env = new ArrayList[height][width];
        int[][] distances = new int[height][width];
        for (int[] d : distances) {
            Arrays.fill(d, -1);
        }
        ArrayList<Integer> exits = new ArrayList<>();
        int c = 0;
        while (in.hasNextLine()) {
            phrase = in.nextLine();
            for (int j = 0; j < phrase.length(); j++) {
                input[c][j] = phrase.charAt(j);
            }
            c++;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                env[i][j] = new ArrayList<>();
                if (input[2 * i][2 * j + 1] == ' ') {
                    if (i != 0) {
                        env[i][j].add((i - 1) * width + j);
                    } else {
                        if (!exits.contains(i * width + j)) {
                            exits.add(i * width + j);
                        }
                    }
                }
                if (input[2 * i + 2][2 * j + 1] == ' ') {
                    if (i != height - 1) {
                        env[i][j].add((i + 1) * width + j);
                    } else {
                        if (!exits.contains(i * width + j)) {
                            exits.add(i * width + j);
                        }
                    }

                }
                if (input[2 * i + 1][2 * j] == ' ') {
                    if (j != 0) {
                        env[i][j].add(i * width + j - 1);
                    } else {
                        if (!exits.contains(i * width + j)) {
                            exits.add(i * width + j);
                        }
                    }
                }
                if (input[2 * i + 1][2 * j + 2] == ' ') {
                    if (j != width - 1) {
                        env[i][j].add(i * width + j + 1);
                    } else {
                        if (!exits.contains(i * width + j)) {
                            exits.add(i * width + j);
                        }
                    }
                }

            }
        }
        int numVisited = 0;
        int dist = 0;
        boolean[][] explored = new boolean[height][width];
        ArrayList<Integer> frontier = new ArrayList<>();
        for (int i = 0; i < exits.size(); i++) {
            System.out.println(i);
            dist = 0;
            for (boolean[] e : explored) {
                Arrays.fill(e, false);
            }
            frontier.add(exits.get(i));
            do {
                System.out.println(dist + " " + (System.currentTimeMillis() - startTime) + " " + numVisited);

                ArrayList<Integer> newFront = new ArrayList<>();
                for (int start : frontier) {
                    for (int neighbor : env[start / width][start % width]) {
                        if (!explored[neighbor / width][neighbor % width] && !newFront.contains(neighbor) && !frontier.contains(neighbor)) {
                            newFront.add(neighbor);
                            System.out.println(neighbor);
                        }
                    }
                    if (distances[start / width][start % width] == -1
                            || distances[start / width][start % width] > dist) {
                        distances[start / width][start % width] = dist;
                    }
                    explored[start / width][start % width] = true;
                    numVisited++;
                }
                frontier = newFront;
                dist++;
            } while (frontier.size() != 0);
        }

        System.out.println("found distances");
        int maxDist = 0;
        for (int[] d : distances) {
            for (int i : d) {
                if (i > maxDist) {
                    maxDist = i;
                }
            }
        }
        out.println(maxDist + 1);

        in.close();
        out.close();
    }
}
