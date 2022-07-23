/*
ID: ssk49881
LANG: JAVA
TASK: prob1
*/

import java.io.*;
import java.util.*;

public class prob1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            int q = Integer.parseInt(in.readLine());
            ArrayList<Integer> s1 = new ArrayList<>();
            ArrayList<Integer> s2 = new ArrayList<>();
            for (int size = 2 + q % 2; q / size + 1 - (size - 1) > 0; size += 2) {
                if (q % size != 0 || q / size - (size - 1) <= 0 || (q / size) % 2 != q % 2) {
                    continue;
                }
                s1.add(q / size - (size - 1));
                s2.add(q / size + (size - 1));
                // System.out.println(size);
                // System.out.println(q + ": [" + (q / size - (size - 1)) + ", " + (q / size +
                // (size - 1)) + "]");
            }
            Collections.sort(s1);
            Collections.sort(s2);
            for (int j = 0; j < s1.size(); j++) {
                System.out.println(q + ": [" + s1.get(j) + ", " + s2.get(j) + "]");
            }
            if (s1.size() == 0) {
                System.out.println(q + ": impossible");
            }

        }

        in.close();
        out.close();
    }
}