/*
ID: ssk49881
LANG: JAVA
TASK: hps
*/

import java.io.*;
import java.util.*;

public class hps {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("hps.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));
        int numGames = Integer.parseInt(in.readLine());
        int[] play = new int[numGames];
        for (int i = 0; i < numGames; i++) {
            String h = in.readLine();
            int val = 0;
            if (h.equals("H")) {
                val = 0;
            } else if (h.equals("S")) {
                val = 1;
            } else {
                val = 2;
            }
            play[i] = val;
        }
        int[][] sums = new int[numGames][3];
        sums[0][play[0]]++;
        for (int i = 1; i < numGames; i++) {
            sums[i][0] = sums[i - 1][0];
            sums[i][1] = sums[i - 1][1];
            sums[i][2] = sums[i - 1][2];
            sums[i][play[i]]++;
        }
        int maxWins = 0;
        for (int i = 0; i < numGames; i++) {
            int max1 = Math.max(Math.max(sums[i][0], sums[i][1]), sums[i][2]);
            int max2 = Math.max(Math.max(sums[numGames - 1][0] - sums[i][0], sums[numGames - 1][1] - sums[i][1]),
                    sums[numGames - 1][2] - sums[i][2]);
            // System.out.println(i + " " + max1 + " " + max2 + " " + (max1 + max2));
            if (max1 + max2 > maxWins) {
                maxWins = max1 + max2;
            }
        }
        out.println(maxWins);

        in.close();
        out.close();
    }
}