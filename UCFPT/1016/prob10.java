/*
ID: ssk49881
LANG: JAVA
TASK: prob10
*/

import java.io.*;
import java.util.*;

public class prob10 {
    public static int MAX_ELEMENT = 100;
    public static int[][] numSolutions;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        numSolutions = new int[MAX_ELEMENT * MAX_ELEMENT + 1][MAX_ELEMENT + 1];
        numSolutions[0][0] = 1;
        for (int add = 1; add <= MAX_ELEMENT; add++) {
            int sq = add * add;
            for (int sum = 0; sum < numSolutions.length - sq; sum++) {
                for (int prev = 0; prev + 2 <= add || prev == 0; prev++) {
                    numSolutions[sum + sq][add] += numSolutions[sum][prev];
                }
            }
        }
        int[] answers = new int[numSolutions.length];
        for (int i = 0; i < numSolutions.length; i++) {
            for (int j = 0; j < numSolutions[i].length; j++) {
                if (numSolutions[i][j] > 0) {
                    // System.out.println(i + " " + j + " " + numSolutions[i][j]);
                }
                answers[i] += numSolutions[i][j];
            }
        }
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            int q = Integer.parseInt(in.readLine());
            System.out.println(answers[q]);
        }

        in.close();
        out.close();
    }
}