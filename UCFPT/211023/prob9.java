/*
ID: ssk49881
LANG: JAVA
TASK: prob9
*/

import java.io.*;
import java.util.*;

public class prob9 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            String s1 = in.readLine().replace(" ", "").replace("{", "").replace("}", "").toUpperCase();
            String s2 = in.readLine().replace(" ", "").replace("{", "").replace("}", "").toUpperCase();
            String[] st1 = s1.split(",");
            String[] st2 = s2.split(",");
            Set<String> set = new HashSet<>();
            Set<String> set2 = new HashSet<>();
            for (String s : st1) {
                set.add(s);
            }
            for(String s : st2){
                set2.add(s);
            }
            boolean subset = true;
            for (String s : set2) {
                subset = set.remove(s) && subset;
            }
            subset = subset && set.size() > 0;
            System.out.println((i + 1) + ": " + (subset ? "YES" : "NO"));
        }

        in.close();
        out.close();
    }
}