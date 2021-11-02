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
        Scanner in = new Scanner(new File("prefix.in"));
        PrintWriter out = new PrintWriter(new File("prefix.out"));
        primitives = new ArrayList<>();

        String phrase = in.nextLine();
        while (phrase.charAt(0) != '.') {
            String[] primlist = phrase.split(" ");
            for (String prim : primlist) {
                primitives.add(prim);
            }
            phrase = in.nextLine();
        }
        System.out.println("Start solving");
        while (in.hasNextLine()) {
            sequence += in.nextLine();
        }
        System.out.println("Start solving");
        for (int i = 0; i < primitives.size(); i++) {
            String prim = primitives.get(i);
            if (findPrefix(0, prim) == prim.length()) {
                primitives.remove(i);
                i--;
            }
        }
        System.out.println("Size: " + primitives.size());
        
        System.out.println("Start solving");
        int len = findPrefix(0, sequence);
        out.println(len);

        in.close();
        out.close();
    }

    public static int findPrefix(int currIndex, String word) {
        if (currIndex >= word.length()) {
            return currIndex;
        }
        int maxIndex = currIndex;
        System.out.println("current index:" + currIndex);
        for (String prim : primitives) {
            if (!prim.equals(word) && word.indexOf(prim, currIndex) == currIndex) {
                System.out.println("Primitive:" + prim);
                int newIndex = findPrefix(currIndex + prim.length(), word);
                if (newIndex > maxIndex) {
                    maxIndex = newIndex;
                }
                if (maxIndex >= word.length()) {
                    return maxIndex;
                }
            }
        }
        System.out.println(maxIndex);
        return maxIndex;
    }
}