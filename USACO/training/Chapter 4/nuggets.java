/*
ID: ssk49881
LANG: JAVA
TASK: nuggets
*/

import java.io.*;
import java.util.*;

public class nuggets {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("nuggets.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nuggets.out")));

        int numNuggets = Integer.parseInt(in.readLine());
        int[] nuggetSizes = new int[numNuggets];
        for (int i = 0; i < numNuggets; i++) {
            nuggetSizes[i] = Integer.parseInt(in.readLine());
        }
        Arrays.sort(nuggetSizes);
        long[] match = new long[nuggetSizes[0]];
        int smallest = match.length;
        Arrays.fill(match, -1);
        match[0] = 0;
        for (int i = 1; i < numNuggets; i++) {
            int rem = nuggetSizes[i] % smallest;
            ArrayList<Integer> alreadyMet = new ArrayList<>();
            alreadyMet.add(rem);
            if (match[rem] == -1 || match[rem] > nuggetSizes[i]) {
                match[rem] = nuggetSizes[i];
            }
            long remMult = 2;
            int placeholder = (rem * 2) % smallest;
            while (!alreadyMet.contains(placeholder)) {
                alreadyMet.add(placeholder);
                if (match[placeholder] == -1 || match[placeholder] > nuggetSizes[i] * remMult) {
                    match[placeholder] = nuggetSizes[i] * remMult;
                    // System.out.println(placeholder + " " + match[placeholder] + " " + remMult);
                }
                remMult++;
                placeholder = (placeholder + rem) % smallest;
            }
            // System.out.println(placeholder + " " + match[placeholder] + " " + remMult);
        }
        System.out.println(Arrays.toString(match));
        for (int i = 0; i < smallest; i++) {
            if (match[i] == -1) {
                continue;
            }
            for (int j = 0; j < smallest; j++) {
                if (match[j] == -1) {
                    continue;
                }
                //System.out.println((i + j) % smallest + " " + i + " " + j + " " + match[i] + " " + match[j]);
                if (match[(i + j) % smallest] == -1 || match[(i + j) % smallest] > match[i] + match[j]) {
                    match[(i + j) % smallest] = match[i] + match[j];
                    System.out.println((i + j) % smallest + " " + i + " " + j + " " + match[i] + " " + match[j]);
                }
            }
        }
        System.out.println(Arrays.toString(match));
        long answer = 0;
        for (int i = 0; i < smallest; i++) {
            if (match[i] == -1) {
                System.out.println(i);
                answer = 0;
                break;
            }
            if (match[i] > answer) {
                answer = match[i] - smallest;
            }
        }
        out.println(answer);

        in.close();
        out.close();
    }
}