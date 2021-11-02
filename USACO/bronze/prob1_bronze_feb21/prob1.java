/*
ID: ssk49881
LANG: JAVA
TASK: prob1
*/

import java.io.*;
import java.util.*;

public class prob1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        Map<String, Integer> signs = new HashMap<>();
        Map<String, Integer> cowDiff = new HashMap<>();
        Map<String, Integer> cowYear = new HashMap<>();
        signs.put("Ox", 0);
        signs.put("Tiger", 1);
        signs.put("Rabbit", 2);
        signs.put("Dragon", 3);
        signs.put("Snake", 4);
        signs.put("Horse", 5);
        signs.put("Goat", 6);
        signs.put("Monkey", 7);
        signs.put("Rooster", 8);
        signs.put("Dog", 9);
        signs.put("Pig", 10);
        signs.put("Rat", 11);
        int[][][] diff = new int[12][12][2];
        for (int i = 0; i < diff.length; i++) {
            for (int j = 0; j < diff[i].length; j++) {
                if (i == j) {
                    diff[i][j][0] = -12;
                    diff[i][j][1] = 12;
                } else if (i > j) {
                    diff[i][j][0] = i - j - 12;
                    diff[i][j][1] = i - j;
                } else {
                    diff[i][j][0] = i - j;
                    diff[i][j][1] = i - j + 12;
                }
            }
        }

        int numCows = Integer.parseInt(in.readLine());
        cowDiff.put("Bessie", 0);
        cowYear.put("Bessie", 0);
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String cName = tokenizer.nextToken();
            tokenizer.nextToken();
            tokenizer.nextToken();
            int prevNext = tokenizer.nextToken().equals("previous") ? 0 : 1;
            int year = signs.get(tokenizer.nextToken());
            tokenizer.nextToken();
            tokenizer.nextToken();
            String oName = tokenizer.nextToken();
            int years = diff[year][cowYear.get(oName)][prevNext];
            cowYear.put(cName, year);
            cowDiff.put(cName, cowDiff.get(oName) + years);
            // System.out.println(cName + " " + cowDiff.get(cName));
        }
        out.println(Math.abs(cowDiff.get("Elsie")));

        in.close();
        out.close();
    }
}