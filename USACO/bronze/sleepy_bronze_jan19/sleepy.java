/*
ID: ssk49881
LANG: JAVA
TASK: sleepy
*/

import java.io.*;
import java.util.*;

public class sleepy {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("sleepy.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sleepy.out")));
        int numCows = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        ArrayList<Integer> order = new ArrayList<>();
        for (int i = 0; i < numCows; i++) {
            order.add(Integer.parseInt(tokenizer.nextToken()));
        }
        int maxFix = -1;
        for (int i = 0; i < order.size(); i++) {
            int val = order.get(i);
            int count = 0;
            for (int j = 0; j < i; j++) {
                if (order.get(j) < val) {
                    count++;
                }
            }
            if (count < val - 1) {
                maxFix = i;
            }
        }
        out.println(maxFix + 1);

        in.close();
        out.close();
    }
}