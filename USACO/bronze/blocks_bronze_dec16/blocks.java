/*
ID: ssk49881
LANG: JAVA
TASK: blocks
*/

import java.io.*;
import java.util.*;

public class blocks {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("blocks.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("blocks.out")));
        int numBlocks = Integer.parseInt(in.readLine());
        int[][][] counts = new int[numBlocks][2][26];
        for (int i = 0; i < numBlocks; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < 2; j++) {
                char[] word = tokenizer.nextToken().toCharArray();
                for (int k = 0; k < word.length; k++) {
                    counts[i][j][word[k] - 'a']++;
                }
            }
        }
        int[] blocksNeeded = new int[26];
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < numBlocks; j++) {
                blocksNeeded[i] += Math.max(counts[j][0][i], counts[j][1][i]);
            }
            out.println(blocksNeeded[i]);
        }

        in.close();
        out.close();
    }
}