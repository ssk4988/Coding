/*
ID: ssk49881
LANG: JAVA
TASK: holstein
*/

import java.io.*;
import java.util.*;

public class holstein {
    public static int[] requirements;
    public static int[][] feeds;
    public static ArrayList<String> potentialSolutions = new ArrayList<>();
    public static ArrayList<String> sol = new ArrayList<>();
    public static int numFeeds;
    public static int numVitamins;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("holstein.in"));
        PrintWriter out = new PrintWriter(new File("holstein.out"));
        numVitamins = Integer.parseInt(in.nextLine());
        requirements = new int[numVitamins];
        String phrase = in.nextLine();
        for (int i = 0; i < phrase.split(" ").length; i++) {
            requirements[i] = Integer.parseInt(phrase.split(" ")[i]);
        }
        numFeeds = Integer.parseInt(in.nextLine());
        feeds = new int[numFeeds][numVitamins];
        for (int j = 0; j < numFeeds; j++) {
            phrase = in.nextLine();
            for (int i = 0; i < phrase.split(" ").length; i++) {
                feeds[j][i] = Integer.parseInt(phrase.split(" ")[i]);
            }
        }
        boolean notSolved = true;

        for (int s = 1; notSolved; s++) {
            potentialSolutions = new ArrayList<>();
            generateCombinations(0, s, "");

            for (String str : potentialSolutions) {
                if (isSolution(str)) {
                    sol.add(str);
                    notSolved = false;
                }
            }
        }
        Collections.sort(sol);
        String solstr = sol.get(0);
        out.print(solstr.length());
        for (int i = 0; i < solstr.length(); i++) {
            out.print(" " + (solstr.charAt(i) - 'A' + 1));
        }

        out.println();

        in.close();
        out.close();
    }

    public static void generateCombinations(int index, int length, String current) {
        if (length == 0) {
            potentialSolutions.add(current);
            return;
        }
        String vitaminString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = index; i < numFeeds; i++) {
            generateCombinations(i + 1, length - 1, current + vitaminString.charAt(i));
        }
        return;
    }

    public static boolean isSolution(String str) {
        int[] sum = new int[numVitamins];
        for (char chr : str.toCharArray()) {
            for (int j = 0; j < numVitamins; j++) {
                sum[j] += feeds[chr - 'A'][j];
            }
        }
        for (int i = 0; i < numVitamins; i++) {
            if (sum[i] < requirements[i]) {
                return false;
            }
        }
        return true;
    }
}