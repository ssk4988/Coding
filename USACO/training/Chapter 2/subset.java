/*
ID: ssk49881
LANG: JAVA
TASK: subset
*/

import java.io.*;
import java.util.*;

public class subset {
    public static ArrayList<String> subsets = new ArrayList<>();
    public static int partialSum;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("subset.in"));
        PrintWriter out = new PrintWriter(new File("subset.out"));
        int n = Integer.parseInt(in.nextLine());
        if (n * (n + 1) / 2 % 2 == 1) {
            System.out.println(3);
            out.println(0);
        } else {
            double[][] sumsets = new double[n + 1][n * (n + 1) / 2 + 1];
            sumsets[1][0] = 1;
            sumsets[1][1] = 1;
            for (int i = 2; i <= n; i++) {
                for (int j = 0; j < sumsets[0].length; j++) {
                    sumsets[i][j] += sumsets[i - 1][j];
                    if (i + j < sumsets[0].length) {
                        sumsets[i][i + j] += sumsets[i - 1][j];
                    }
                }
            }
            System.out.printf("%.0f\n", sumsets[n][n * (n + 1) / 4] / 2);
            if (sumsets[n][n * (n + 1) / 4] / 2 == 0) {
                out.println(3);
            } else {
                out.printf("%.0f\n", sumsets[n][n * (n + 1) / 4] / 2);
            }

        }

        in.close();
        out.close();
    }

}