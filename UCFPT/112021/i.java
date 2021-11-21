/*
ID: ssk49881
LANG: JAVA
TASK: i
*/

import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numWords = tokenizer.countTokens();
        String[] words = new String[numWords];
        int[] wordlengths = new int[numWords];
        int[] prefix = new int[numWords + 1];
        for (int i = 0; i < numWords; i++) {
            words[i] = tokenizer.nextToken();
            wordlengths[i] = words[i].length();
            prefix[i + 1] += wordlengths[i];
            prefix[i + 1] += prefix[i];
        }
        tokenizer = new StringTokenizer(in.readLine());
        int lower = Integer.parseInt(tokenizer.nextToken());
        int higher = Integer.parseInt(tokenizer.nextToken());
        int buffer = 0;
        int[] answers = new int[higher - lower + 1];
        for (int target = higher; target >= lower; target--) {
            if (buffer > 0) {
                answers[target - lower] = answers[target - lower + 1];
                // System.out.println(prevAnswer);
                buffer--;
                continue;
            }
            buffer = Integer.MAX_VALUE;
            ArrayList<Integer> lineEnds = new ArrayList<>();
            lineEnds.add(-1);
            for (int i = 0; i < numWords;) {
                // String s = "";
                int prev = lineEnds.get(lineEnds.size() - 1);
                // String prevString = "";
                i = prev + 1;
                while (i < numWords && prefix[i + 1] - prefix[prev + 1] + (i - prev - 1) <= target) {
                    if (buffer > target - (prefix[i + 1] - prefix[prev + 1] + (i - prev - 1))) {
                        buffer = target - (prefix[i + 1] - prefix[prev + 1] + (i - prev - 1));
                    }
                    // System.out.println(i);
                    // prevString = s;
                    if (i - prev > 1) {
                        // s += ".";
                    }
                    // s += words[i];
                    i++;
                }
                // System.out.println(s + " " + i + " " + length);

                if ((prefix[i] - prefix[prev + 1] + (i - prev - 2)) > target) {
                    i--;
                    // s = prevString;
                }
                // while (s.length() < target) {
                // s += ".";
                // }

                lineEnds.add(i - 1);
                // System.out.println(s + " " + s.length());
            }
            // System.out.println(lineEnds);
            answers[target - lower] = lineEnds.size() - 2;
            for (int i = 0; i < lineEnds.size() - 1; i++) {
                answers[target - lower] += wordlengths[lineEnds.get(i) + 1];
            }
            // System.out.println(sum + " " + buffer);
        }
        for(int i : answers){
            System.out.println(i);
        }
        in.close();
        out.close();
    }
}