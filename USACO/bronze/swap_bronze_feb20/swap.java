/*
ID: ssk49881
LANG: JAVA
TASK: swap
*/

import java.io.*;
import java.util.*;

public class swap {
    public static int numCows;
    public static int numOperations;
    public static int a1;
    public static int a2;
    public static int b1;
    public static int b2;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("swap.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("swap.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numCows = Integer.parseInt(tokenizer.nextToken());
        numOperations = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        a1 = Integer.parseInt(tokenizer.nextToken());
        a2 = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        b1 = Integer.parseInt(tokenizer.nextToken());
        b2 = Integer.parseInt(tokenizer.nextToken());
        int[] finalCows = new int[numCows + 1];
        for (int i = 1; i < numCows + 1; i++) {
            ArrayList<Integer> seen = new ArrayList<>();
            seen.add(i);
            int current = operation(i);
            int operationsPerformed = 1;
            while (operationsPerformed < numOperations && current != i) {
                current = operation(current);
                operationsPerformed++;
            }
            int totalOps = numOperations % operationsPerformed + operationsPerformed;
            while (operationsPerformed < totalOps) {
                current = operation(current);
                operationsPerformed++;
            }
            finalCows[current] = i;
        }
        for (int i = 1; i < numCows + 1; i++) {
            out.println(finalCows[i]);
        }
        in.close();
        out.close();
    }

    public static int operation(int start) {
        if (start >= a1 && start <= a2) {
            start = a2 - (start - a1);
        }
        if (start >= b1 && start <= b2) {
            start = b2 - (start - b1);
        }
        return start;
    }
}