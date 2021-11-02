/*
ID: ssk49881
LANG: JAVA
TASK: ratios
*/

import java.io.*;
import java.util.*;

public class ratios {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("ratios.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ratios.out")));

        int[][] feeds = new int[4][3];
        for (int i = 0; i < 4; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < 3; j++) {
                feeds[i][j] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        boolean works = false;
        loop: for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                for (int k = 0; k < 100; k++) {
                    double first = 1.0 * (i * feeds[1][0] + j * feeds[2][0] + k * feeds[3][0]) / feeds[0][0];
                    double second = 1.0 * (i * feeds[1][1] + j * feeds[2][1] + k * feeds[3][1]) / feeds[0][1];
                    double third = 1.0 * (i * feeds[1][2] + j * feeds[2][2] + k * feeds[3][2]) / feeds[0][2];
                    if (i == 0 && j == 38 && k == 7) {
                        System.out.println("first: " + first);
                        System.out.println("second: " + second);
                        System.out.println("third: " + third);
                    }
                    if (first != 0) {
                        if ((first == second || feeds[0][0] == 0 || feeds[0][1] == 0)
                                && (second == third || feeds[0][1] == 0 || feeds[0][2] == 0)) {
                            if (first == (int) (first)) {
                                out.println(i + " " + j + " " + k + " " + ((int) first));
                                works = true;
                                break loop;
                            }
                        }
                    }
                }
            }
        }

        if (!works) {
            out.println("NONE");
        }

        in.close();
        out.close();
    }
}