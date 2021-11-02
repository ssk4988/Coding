import java.io.*;
import java.util.*;

public class gymnastics {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("gymnastics.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gymnastics.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numTrials = Integer.parseInt(tokenizer.nextToken());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        boolean[][] testConsistency = new boolean[numCows][numCows];
        for (int i = 0; i < numCows; i++) {
            for (int j = 0; j < numCows; j++) {
                if (i != j) {
                    testConsistency[i][j] = true;
                }
            }
        }
        int[][] trials = new int[numCows][numTrials];
        for (int i = 0; i < numTrials; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < numCows; j++) {
                trials[Integer.parseInt(tokenizer.nextToken()) - 1][i] = j;
            }
        }
        int numConsistent = 0;
        for (int i = 0; i < numCows; i++) {
            next: for (int j = 0; j < numCows; j++) {
                if (!testConsistency[i][j]) {
                    continue;
                }
                for (int k = 0; k < numTrials; k++) {
                    if (trials[i][k] >= trials[j][k]) {
                        continue next;
                    }
                }
                numConsistent++;
                // System.out.println(i + " " + j);
                testConsistency[j][i] = false;
            }
        }
        out.println(numConsistent);

        in.close();
        out.close();
    }
}