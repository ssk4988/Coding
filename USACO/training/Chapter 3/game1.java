/*
ID: ssk49881
LANG: JAVA
TASK: game1
*/

import java.io.*;
import java.util.*;

public class game1 {
    public static int[] gameBoard;
    public static int[][] utility;
    public static int NULL = -1000000;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("game1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("game1.out")));
        int size = Integer.parseInt(in.readLine());
        gameBoard = new int[size];
        utility = new int[size][size];
        for (int[] u : utility) {
            Arrays.fill(u, NULL);
        }
        String line = null;
        int ind = 0;
        int sum = 0;
        while ((line = in.readLine()) != null) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            while (tokenizer.hasMoreTokens()) {
                gameBoard[ind] = Integer.parseInt(tokenizer.nextToken());
                sum += gameBoard[ind];
                ind++;
            }
        }
        int[] result = maximize(new int[] { 0, size - 1 });
        int p1 = (sum + result[2]) / 2;
        int p2 = sum - p1;
        out.println(p1 + " " + p2);

        in.close();
        out.close();
    }

    public static int[] maximize(int[] state) {
        if (utility[state[0]][state[1]] != NULL) {
            return new int[] { 0, 0, utility[state[0]][state[1]] };
        }
        if (state[0] >= state[1]) {
            int[] returnVal = new int[3];
            returnVal[2] = gameBoard[state[0]];
            utility[state[0]][state[1]] = returnVal[2];
            return returnVal;
        }
        int[] maxChildMaxUtility = new int[3];
        maxChildMaxUtility[2] = Integer.MIN_VALUE;
        int[] childState = { state[0], state[1] };
        for (int i : new int[] { 0, 1 }) {
            if (i == 0) {
                childState[0] = state[0] + 1;
                childState[1] = state[1];
            } else {
                childState[0] = state[0];
                childState[1] = state[1] - 1;
            }
            int[] value = minimize(childState);
            value[2] += gameBoard[state[i]];
            if (value[2] > maxChildMaxUtility[2]) {
                maxChildMaxUtility = new int[] { childState[0], childState[1], value[2] };
            }
        }
        utility[state[0]][state[1]] = maxChildMaxUtility[2];
        return maxChildMaxUtility;
    }

    public static int[] minimize(int[] state) {
        if (utility[state[0]][state[1]] != NULL) {
            return new int[] { 0, 0, utility[state[0]][state[1]] };
        }
        if (state[0] >= state[1]) {
            int[] returnVal = new int[3];
            returnVal[2] = -gameBoard[state[0]];
            utility[state[0]][state[1]] = returnVal[2];
            return returnVal;
        }
        int[] minChildMinUtility = new int[3];
        minChildMinUtility[2] = Integer.MAX_VALUE;
        int[] childState = { state[0], state[1] };
        for (int i : new int[] { 0, 1 }) {
            if (i == 0) {
                childState[0] = state[0] + 1;
                childState[1] = state[1];
            } else {
                childState[0] = state[0];
                childState[1] = state[1] - 1;
            }
            int[] value = maximize(childState);
            value[2] -= gameBoard[state[i]];
            if (value[2] < minChildMinUtility[2]) {
                minChildMinUtility = new int[] { childState[0], childState[1], value[2] };
            }
        }
        utility[state[0]][state[1]] = minChildMinUtility[2];
        return minChildMinUtility;
    }
}