/*
ID: ssk49881
LANG: JAVA
TASK: lemonade
*/

import java.io.*;
import java.util.*;

public class lemonade {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("lemonade.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lemonade.out")));
        int numCows = Integer.parseInt(in.readLine());
        int[] waits = new int[numCows];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numCows; i++) {
            waits[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(waits);
        ArrayList<Integer> line = new ArrayList<>();
        for (int i = numCows - 1; i >= 0; i--) {
            int wait = waits[i];
            if (line.size() <= wait) {
                line.add(wait);
            }
        }
        out.println(line.size());

        in.close();
        out.close();
    }
}