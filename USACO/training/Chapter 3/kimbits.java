/*
ID: ssk49881
LANG: JAVA
TASK: kimbits
*/

import java.io.*;
import java.util.*;

public class kimbits {
    public static long[] factorials;
    public static long[][] combinations;
    public static long numInSet;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("kimbits.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("kimbits.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numBits = Integer.parseInt(tokenizer.nextToken());
        int maxOnes = Integer.parseInt(tokenizer.nextToken());
        numInSet = Long.parseLong(tokenizer.nextToken());
        factorials = new long[numBits + 1];
        combinations = new long[numBits + 1][numBits + 1];
        for (int n = 0; n <= numBits; n++) {
            long nCk = 1;
            for (int k = 0; k <= n; k++) {
                combinations[n][k] = nCk;
                nCk = nCk * (n - k) / (k + 1);
            }
        }
        out.println(getNumInSet(numBits, maxOnes, 0));
        in.close();
        out.close();
    }

    public static String getNumInSet(int strLength, int maxOnes, long counter) {
        String solution = "";
        if (strLength <= 0) {
            return solution;
        }
        long newCounter = 0;
        for (int i = 0; i <= Math.min(maxOnes, strLength - 1); i++) {
            newCounter += combinations[strLength - 1][i];
        }
        if (maxOnes > 0 && counter + newCounter < numInSet) {
            // use 1 in current location
            solution = "1" + getNumInSet(strLength - 1, maxOnes - 1, counter + newCounter);
        } else {
            solution = "0" + getNumInSet(strLength - 1, maxOnes, counter);
        }
        System.out.println(solution.charAt(0) + " " + counter + " " + newCounter + " " + strLength + " " + maxOnes);
        return solution;
    }
}