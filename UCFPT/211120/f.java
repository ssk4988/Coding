/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line = in.readLine();
        int num = 1;
        while (!line.equals("0")) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            int cacheSize = Integer.parseInt(tokenizer.nextToken());
            String input = tokenizer.nextToken();
            int[] lastused = new int[26];
            Arrays.fill(lastused, -1);
            System.out.println("Simulation " + num);
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);

                if (c == '!') {
                    ArrayList<Integer> cache = new ArrayList<>();
                    for (int j = 0; j < lastused.length; j++) {
                        if (lastused[j] == -1)
                            continue;
                        cache.add(0, j);
                    }
                    Collections.sort(cache, (s1, s2) -> lastused[s1] - lastused[s2]);
                    for (int j = Math.max(0, cache.size() - cacheSize); j < cache.size(); j++) {
                        System.out.print((char) ('A' + cache.get(j)));
                    }
                    System.out.println();
                    // System.out.println("bruh");
                } else {
                    lastused[c - 'A'] = i;
                }
            }
            line = in.readLine();
            num++;
        }
        in.close();
        out.close();
    }
}