/*
ID: ssk49881
LANG: JAVA
TASK: prob6
*/

import java.io.*;
import java.util.*;

public class prob6 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            ArrayList<Integer> sequence = new ArrayList<>();
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            while (tokenizer.hasMoreTokens()) {
                sequence.add(Integer.parseInt(tokenizer.nextToken()));
            }
            int[] throwB = new int[sequence.size()];
            int[] catchB = new int[sequence.size()];
            for (int j = 0; j < sequence.size(); j++) {
                throwB[j]++;
                catchB[(j + sequence.get(j)) % catchB.length]++;
            }
            boolean solve = true;
            String s = "";
            for (int j = 0; j < sequence.size(); j++) {
                if (throwB[j] > 1 || catchB[j] > 1)
                    solve = false;
                s += sequence.get(j) + " ";

            }
            String t = solve ? "can" : "cannot";
            System.out.println(s + "- " + t + " be juggled");
        }
        in.close();
        out.close();
    }
}