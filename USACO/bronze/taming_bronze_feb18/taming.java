/*
ID: ssk49881
LANG: JAVA
TASK: taming
*/

import java.io.*;
import java.util.*;

public class taming {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("taming.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("taming.out")));
        int numDays = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] data = new int[numDays];
        boolean[] accident = new boolean[numDays];
        accident[0] = true;
        boolean[] possibleaccident = new boolean[numDays];
        Arrays.fill(possibleaccident, true);
        int numaccident = 0;
        int numpossible = 0;
        boolean condition = true;
        for (int i = 0; i < numDays; i++) {
            data[i] = Integer.parseInt(tokenizer.nextToken());
            if (data[i] != -1) {
                accident[i - data[i]] = true;
                if (data[i] != 0) {
                    for (int j = i - data[i] + 1; j <= i; j++) {
                        if (accident[j])
                            condition = false;
                        possibleaccident[j] = false;
                    }
                }

            }
        }
        for (int i = 0; i < numDays; i++) {
            if (accident[i])
                numaccident++;
            if (possibleaccident[i])
                numpossible++;
        }
        if (!accident[0])
            condition = false;
        if (condition)
            out.println(numaccident + " " + numpossible);
        else
            out.println("-1");

        in.close();
        out.close();
    }
}