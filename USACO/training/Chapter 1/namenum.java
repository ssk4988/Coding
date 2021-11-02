/*
ID: ssk49881
LANG: JAVA
TASK: namenum
*/

import java.io.*;
import java.util.*;

public class namenum {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("namenum.in"));
        PrintWriter out = new PrintWriter(new File("namenum.out"));
        Scanner inText = new Scanner(new File("dict.txt"));
        String id = in.nextLine();
        int[] mapchars = { 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 1, 7, 7, 8, 8, 8, 9, 9, 9, 1 };
        ArrayList<String> actualNames = new ArrayList<String>();
        while (inText.hasNextLine()) {
            String word = inText.nextLine();
            if (word.length() == id.length()) {
                boolean match = true;
                for (int i = 0; i < word.length(); i++) {
                    if (Integer.parseInt(String.valueOf(id.charAt(i))) != mapchars[word.charAt(i) - 'A']) {
                        match = false;
                    }
                }
                if (match) {
                    actualNames.add(word);
                }
            }
        }
        Collections.sort(actualNames);
        for (String name : actualNames) {
            // System.out.println(name);
            out.println(name);
        }
        if (actualNames.size() == 0) {
            out.println("NONE");
        }
        in.close();
        inText.close();
        out.close();
    }
}