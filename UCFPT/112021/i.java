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
        int[] prefix = new int[numWords];
        for (int i = 0; i < numWords; i++) {
            words[i] = tokenizer.nextToken();
            wordlengths[i] = words[i].length();
            prefix[i] += wordlengths[i];
            if (i > 0)
                prefix[i] += prefix[i - 1];
        }
        tokenizer = new StringTokenizer(in.readLine());
        int lower = Integer.parseInt(tokenizer.nextToken());
        int higher = Integer.parseInt(tokenizer.nextToken());
        ArrayList<Integer> lineStarts = new ArrayList<>();
        lineStarts.add(0);
        int target = lower;
        for (int i = 0; i < numWords;) {
            int length = wordlengths[lineStarts.get(lineStarts.size() - 1)];
            int prev = lineStarts.get(lineStarts.size() - 1);
            while (i + 1 < numWords && length <= target) {
                length += 1 + wordlengths[i + 1];
                i++;
            }
            lineStarts.add(i);
            prev = i;
        }
        System.out.println(lineStarts);

        in.close();
        out.close();
    }
}