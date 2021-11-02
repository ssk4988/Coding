/*
ID: ssk49881
LANG: JAVA
TASK: balancing
*/

import java.io.*;
import java.util.*;

public class balancing {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("balancing.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("balancing.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numPoints = Integer.parseInt(tokenizer.nextToken());
        int maxValue = Integer.parseInt(tokenizer.nextToken());

        int[] xval = new int[numPoints];
        int[] yval = new int[numPoints];
        ArrayList<Integer> xset = new ArrayList<>();
        ArrayList<Integer> yset = new ArrayList<>();
        for (int i = 0; i < numPoints; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if (!xset.contains(x))
                xset.add(x);
            if (!yset.contains(y))
                yset.add(y);
            xval[i] = x;
            yval[i] = y;
        }
        Collections.sort(xset);
        Collections.sort(yset);
        for (int i = 0; i < numPoints; i++) {
            xval[i] = xset.indexOf(xval[i]);
            yval[i] = yset.indexOf(yval[i]);
        }
        int minval = Integer.MAX_VALUE;
        for (int i = 0; i < xset.size() - 1; i++) {
            for (int j = 0; j < yset.size() - 1; j++) {
                int[][] values = new int[2][2];
                for (int k = 0; k < numPoints; k++) {
                    int xind = xval[k] <= i ? 0 : 1;
                    int yind = yval[k] <= j ? 0 : 1;
                    values[xind][yind]++;
                }
                int val = Math.max(Math.max(values[0][0], values[0][1]), Math.max(values[1][0], values[1][1]));
                if (val < minval)
                    minval = val;
            }
        }
        out.println(minval);

        in.close();
        out.close();
    }
}