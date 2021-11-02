/*
ID: ssk49881
LANG: JAVA
TASK: range
*/

import java.io.*;
//import java.util.*;

public class range {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("range.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("range.out")));
        int size = Integer.parseInt(in.readLine());
        int[][] fields = new int[size][size];
        int[][] fieldsCopy = new int[size][size];
        for (int i = 0; i < size; i++) {
            String phrase = in.readLine();
            for (int j = 0; j < phrase.length(); j++) {
                fields[i][j] = Integer.parseInt(phrase.substring(j, j + 1));
            }
        }
        for (int i = 1; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size - i; j++) {
                for (int k = 0; k < size - i; k++) {
                    fieldsCopy[j][k] = fields[j][k] * fields[j][k + 1] * fields[j + 1][k]
                            * fields[j + 1][k + 1];
                    if (fieldsCopy[j][k] == 1) {
                        count++;
                    }
                }
            }
            if (count != 0) {
                out.println((i + 1) + " " + count);
            }
            fields = fieldsCopy.clone();
        }

        in.close();
        out.close();
    }
}