/*
ID: ssk49881
LANG: JAVA
TASK: notlast
*/

import java.io.*;
import java.util.*;

public class notlast {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("notlast.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("notlast.out")));
        int numEntries = Integer.parseInt(in.readLine());
        TreeMap<String, Integer> map = new TreeMap<>();
        map.put("Bessie", 0);
        map.put("Elsie", 0);
        map.put("Daisy", 0);
        map.put("Gertie", 0);
        map.put("Annabelle", 0);
        map.put("Maggie", 0);
        map.put("Henrietta", 0);
        for (int i = 0; i < numEntries; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String cow = tokenizer.nextToken();
            int milk = Integer.parseInt(tokenizer.nextToken());
            map.put(cow, map.get(cow) + milk);
        }
        int min = Integer.MAX_VALUE;
        for (String k : map.keySet()) {
            min = Math.min(min, map.get(k));
        }
        int min2 = Integer.MAX_VALUE;
        String cow = "";
        int times = 0;
        for (String k : map.keySet()) {
            if (map.get(k) < min2 && map.get(k) > min) {
                times = 0;
                min2 = map.get(k);
                cow = k;
            }
            if (map.get(k) == min2) {
                times++;
            }
        }
        // System.out.println(min + " " + min2 + " " + times);
        if (times != 1) {
            out.println("Tie");
        } else {
            out.println(cow);
        }

        in.close();
        out.close();
    }
}