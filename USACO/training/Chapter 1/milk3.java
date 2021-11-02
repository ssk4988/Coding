/*
ID: ssk49881
LANG: JAVA
TASK: milk3
*/

import java.io.*;
import java.util.*;

public class milk3 {
    public static int[] maxCapacity = new int[3];
    public static ArrayList<Integer> solutions;
    public static int nodesExpanded = 0;
    public static Stack<String> frontier = new Stack<>();

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("milk3.in"));
        PrintWriter out = new PrintWriter(new File("milk3.out"));
        String phrase = in.nextLine();
        maxCapacity[0] = Integer.parseInt(phrase.split(" ")[0]);
        maxCapacity[1] = Integer.parseInt(phrase.split(" ")[1]);
        maxCapacity[2] = Integer.parseInt(phrase.split(" ")[2]);
        int[] initial = { 0, 0, maxCapacity[2] };
        solutions = new ArrayList<>();
        expand(initial);
        System.out.println("Nodes Expanded: " + nodesExpanded);
        Collections.sort(solutions);
        for (int i = 0; i < solutions.size(); i++) {
            System.out.println(solutions.get(i));
            out.print(solutions.get(i));
            if (i != solutions.size() - 1) {
                out.print(" ");
            }
        }
        out.println();

        in.close();
        out.close();
    }

    public static int[] pour(int[] cans, int give, int receive) {
        int[] copy = cans.clone();
        copy[receive] = Math.min(maxCapacity[receive], cans[receive] + cans[give]);
        copy[give] = cans[give] - (copy[receive] - cans[receive]);
        return copy;
    }

    public static void expand(int[] buckets) {
        if (buckets[0] == 0) {
            if (!solutions.contains(buckets[2])) {
                solutions.add(buckets[2]);
            }
        }
        for (int i = 0; i < buckets.length; i++) {
            if (buckets[i] == 0) {
                continue;
            }
            for (int j = 0; j < buckets.length; j++) {
                if (i == j || buckets[j] == maxCapacity[j]) {
                    continue;
                }
                nodesExpanded++;
                int[] newbuckets = pour(buckets, i, j);
                if (!frontier.contains(newbuckets[0] + " " + newbuckets[1] + " " + newbuckets[2])) {
                    System.out.println("Pour " + buckets[i] + "milk from " + i + " to " + j);
                    frontier.add(buckets[0] + " " + buckets[1] + " " + buckets[2]);
                    expand(pour(buckets, i, j));
                    frontier.pop();
                }

            }
        }

    }
}