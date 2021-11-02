/*
ID: ssk49881
LANG: JAVA
TASK: mooyomooyo
*/

import java.io.*;
import java.util.*;

public class mooyomooyo {
    public static int height;
    public static int k;
    public static int[][] state;
    public static int[][] components;
    public static int numComponents = 0;
    public static ArrayList<Integer> numPer = new ArrayList<>();
    public static boolean cont = true;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("mooyomooyo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mooyomooyo.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        height = Integer.parseInt(tokenizer.nextToken());
        k = Integer.parseInt(tokenizer.nextToken());
        state = new int[height][10];
        for (int i = 0; i < height; i++) {
            String s = in.readLine();
            for (int j = 0; j < 10; j++) {
                state[i][j] = Integer.parseInt(s.substring(j, j + 1));
            }
        }
        components = new int[height][10];
        while (cont) {
            for (int[] i : components) {
                Arrays.fill(i, -2);
            }
            numPer = new ArrayList<>();
            numComponents = 0;
            cont = false;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < 10; j++) {
                    if (state[i][j] != 0 && components[i][j] == -2) {
                        flood_fill(i * 10 + j);
                        numComponents++;
                    }
                }
            }
            // printState();
            // printComp();
            for (int j = 0; j < 10; j++) {
                int gapsize = 0;
                for (int i = height - 1; i >= 0; i--) {
                    if (state[i][j] == 0) {
                        gapsize++;
                    } else {
                        if (gapsize > 0) {
                            state[i + gapsize][j] = state[i][j];
                            state[i][j] = 0;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < 10; j++) {
                out.print(state[i][j]);
            }
            out.println();
        }

        in.close();
        out.close();
    }

    public static void printComp() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < 10; j++) {
                System.out.print(Math.abs(components[i][j]) + ",");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void printState() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < 10; j++) {
                System.out.print(state[i][j]);
            }
            System.out.println();
        }
    }

    public static void flood_fill(int index) {
        ArrayList<Integer> seen = new ArrayList<>();
        ArrayList<Integer> frontier = new ArrayList<>();
        frontier.add(index);
        while (frontier.size() != 0) {
            int next = frontier.remove(0);
            seen.add(next);
            int i = next / 10;
            int j = next % 10;
            if (i > 0) {
                int index2 = (i - 1) * 10 + j;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i - 1][j] == state[i][j]) {
                    frontier.add(index2);
                }
            }
            if (j > 0) {
                int index2 = i * 10 + j - 1;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i][j - 1] == state[i][j]) {
                    frontier.add(index2);
                }
            }
            if (i < height - 1) {
                int index2 = (i + 1) * 10 + j;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i + 1][j] == state[i][j]) {
                    frontier.add(index2);
                }
            }
            if (j < 10 - 1) {
                int index2 = i * 10 + j + 1;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i][j + 1] == state[i][j]) {
                    frontier.add(index2);
                }
            }
        }
        if (seen.size() >= k) {
            cont = true;
        }
        for (int in : seen) {
            int i = in / 10;
            int j = in % 10;
            components[i][j] = numComponents;
            if (seen.size() >= k) {
                state[i][j] = 0;
            }
        }
    }
}