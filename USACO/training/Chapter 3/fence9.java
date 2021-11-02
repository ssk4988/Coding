/*
ID: ssk49881
LANG: JAVA
TASK: fence9
*/

import java.io.*;
import java.util.*;

public class fence9 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("fence9.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence9.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int x1 = Integer.parseInt(tokenizer.nextToken());
        int y1 = Integer.parseInt(tokenizer.nextToken());
        int x2 = Integer.parseInt(tokenizer.nextToken());

        int maxX = Math.max(x1, x2);
        double slope1 = x1 == 0 ? 1000000 : (double) y1 / x1;
        double slope2 = x1 == x2 ? 1000000 : (double) y1 / (double) (x1 - x2);
        System.out.println(slope1);
        System.out.println(slope2);
        int numPoints = 0;
        for (int x = 1; x < maxX; x++) {
            double num1 = 32000;
            if (slope1 != 1000000) {
                num1 = (slope1 * x) % 1;
                num1 = num1 < 0.001 ? Math.floor((slope1 * x) - 1) : Math.floor((slope1 * x));
            }

            if (slope2 != 1000000 && slope2 < 0) {
                double num2 = 32000;
                num2 = (slope2 * (x - x2)) % 1;
                num2 = num2 < 0.001 ? Math.floor((slope2 * (x - x2)) - 1) : Math.floor((slope2 * (x - x2)));
                num1 = Math.min(num1, num2);
            }
            numPoints += (int) num1;
            if (slope2 != 1000000 && slope2 > 0) {
                double num2 = slope2 * (x - x2);
                num2 = Math.floor(num2);
                num2 = Math.max(num2, 0);
                numPoints -= (int) num2;
            }
        }
        out.println(numPoints);
        in.close();
        out.close();
    }
}