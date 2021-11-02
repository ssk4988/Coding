/*
ID: ssk49881
LANG: JAVA
TASK: snowboots
*/

import java.io.*;
import java.util.*;

public class snowboots {
    public static int[] depths;
    public static int[] maxDepths;
    public static int[] maxSteps;
    public static int numSteps;
    public static int numBoots;
    public static int[][] output;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("snowboots.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("snowboots.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numSteps = Integer.parseInt(tokenizer.nextToken());
        numBoots = Integer.parseInt(tokenizer.nextToken());
        depths = new int[numSteps];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numSteps; i++) {
            depths[i] = Integer.parseInt(tokenizer.nextToken());
        }
        output = new int[numBoots][numSteps];
        for (int[] i : output) {
            Arrays.fill(i, -1);
        }
        maxDepths = new int[numBoots];
        maxSteps = new int[numBoots];
        for (int i = 0; i < numBoots; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            maxDepths[i] = Integer.parseInt(tokenizer.nextToken());
            maxSteps[i] = Integer.parseInt(tokenizer.nextToken());
        }
        out.println(dfs(0, 0));

        in.close();
        out.close();
    }

    public static int dfs(int currentBoot, int currentStep) {
        if (currentBoot == numBoots) {
            return Integer.MAX_VALUE;
        }
        if (output[currentBoot][currentStep] != -1) {
            return output[currentBoot][currentStep];
        }
        if (currentStep == numSteps - 1) {
            return currentBoot;
        }

        int minResult = Integer.MAX_VALUE;
        int currentStepSize = maxSteps[currentBoot];
        int currentDepth = maxDepths[currentBoot];

        minResult = Math.min(dfs(currentBoot + 1, currentStep), minResult);
        if (currentDepth >= depths[currentStep]) {
            int maxBound = Math.min(numSteps - 1, currentStep + currentStepSize);
            for (int i = currentStep + 1; i <= maxBound; i++) {
                if (depths[i] <= currentDepth) {
                    minResult = Math.min(dfs(currentBoot, i), minResult);
                }
            }
        }
        output[currentBoot][currentStep] = minResult;

        return minResult;
    }
}