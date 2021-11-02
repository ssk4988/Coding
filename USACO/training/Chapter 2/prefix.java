/*
ID: ssk49881
LANG: JAVA
TASK: prefix
*/

import java.io.*;
import java.util.*;

public class prefix {
    public static ArrayList<String> primitives;
    public static String sequence = "";

    public static void main(String[] args) throws Exception {
        long startTime = System.currentTimeMillis();
        Scanner in = new Scanner(new File("prefix.in"));
        PrintWriter out = new PrintWriter(new File("prefix.out"));
        primitives = new ArrayList<>();
        int maxPrimLength = 0;

        String phrase = in.nextLine();
        while (phrase.charAt(0) != '.') {
            String[] primlist = phrase.split(" ");
            for (String prim : primlist) {
                primitives.add(prim);
                if (prim.length() > maxPrimLength) {
                    maxPrimLength = prim.length();
                }
            }
            phrase = in.nextLine();
        }
        while (in.hasNextLine()) {
            sequence += in.nextLine();
        }
        boolean[] start = new boolean[sequence.length() + 1];
        int len = sequence.length();
        start[0] = true;
        int best = 0;

        for (int i = 0; i < primitives.size(); i++) {
            String prim = primitives.get(i);
            if (findPrefix(0, prim) == prim.length()) {
                primitives.remove(i);
                i--;
            }
        }
        System.out.println(System.currentTimeMillis() - startTime);
        for (int i = 0; i < len; i++) {
            if (start[i]) {
                for (String prim : primitives) {
                    if (i + prim.length() <= len && sequence.substring(i, i + prim.length()).equals(prim)) {

                        // System.out.println(prim + " " + i + " " + sequence.substring(i, i +
                        // prim.length()));
                        start[i + prim.length()] = true;
                        if (i + prim.length() > best) {
                            best = i + prim.length();
                        }
                    }
                }
            }
        }
        if (start[sequence.length()]) {
            out.println(sequence.length());
        } else {
            out.println(best);
        }
        /*
         * for (int i = 0; i < primitives.size(); i++) { String prim =
         * primitives.get(i); if (findPrefix(0, prim) == prim.length()) {
         * primitives.remove(i); i--; } }
         */
        System.out.println("Size: " + primitives.size());

        System.out.println("Start solving");
        // int len = findPrefix(0, sequence);
        // out.println(len);

        in.close();
        out.close();
    }

    public static int findPrefix(int currIndex, String word) {
        if (currIndex >= word.length()) {
            return currIndex;
        }
        int maxIndex = currIndex;
        for (String prim : primitives) {
            if (!prim.equals(word) && word.indexOf(prim, currIndex) == currIndex) {
                int newIndex = findPrefix(currIndex + prim.length(), word);
                if (newIndex > maxIndex) {
                    maxIndex = newIndex;
                }
                if (maxIndex >= word.length()) {
                    return maxIndex;
                }
            }
        }
        return maxIndex;
    }
}