/*
ID: ssk49881
LANG: JAVA
TASK: milkvisits
*/

import java.io.*;
import java.util.*;

public class milkvisits {
    public static int[] component;
    public static int numFarms;
    public static ArrayList<Integer>[] neighbors;
    public static int[] farmtypes;

    public static void main(String[] args) throws Exception {
        long start_time = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("milkvisits.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milkvisits.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numFarms = Integer.parseInt(tokenizer.nextToken());
        int numFriends = Integer.parseInt(tokenizer.nextToken());
        neighbors = new ArrayList[numFarms];
        component = new int[numFarms];
        Arrays.fill(component, -1);
        farmtypes = new int[numFarms];
        String types = in.readLine();
        for (int i = 0; i < numFarms; i++) {
            if (types.charAt(i) == 'H') {
                farmtypes[i] = 1;
            } else {
                farmtypes[i] = 2;
            }
            neighbors[i] = new ArrayList<>();
        }
        for (int i = 0; i < numFarms - 1; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            neighbors[first].add(second);
            neighbors[second].add(first);
        }
        int numComponents = 0;
        for (int i = 0; i < numFarms; i++) {
            if (component[i] == -1) {
                numComponents++;
                LinkedList<Integer> frontier = new LinkedList<>();
                frontier.add(i);
                while (!frontier.isEmpty()) {
                    int next = frontier.poll();
                    component[next] = numComponents;
                    for (int neighbor : neighbors[next]) {
                        if (component[neighbor] == -1 && farmtypes[neighbor] == farmtypes[next]) {
                            frontier.add(neighbor);
                        }
                    }
                }
            }
        }
        int numRight = 0;
        for (int i = 0; i < numFriends; i++) {
            if (i % 10000 == 0)
                System.out.println(numRight + " " + i + " " + (System.currentTimeMillis() - start_time));
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            String typ = tokenizer.nextToken();
            int typnum = typ.equals("H") ? 1 : 2;
            int output = -1;
            if (component[first] != component[second] || farmtypes[first] == typnum) {
                output = 1;
            } else {
                output = 0;
            }
            out.print(output);
        }
        out.println();
        in.close();
        out.close();
    }
}