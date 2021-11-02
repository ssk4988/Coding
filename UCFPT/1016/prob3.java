/*
ID: ssk49881
LANG: JAVA
TASK: prob3
*/

import java.io.*;
import java.util.*;

public class prob3 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;
        int linecount = 1;
        while ((line = in.readLine()) != null) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            if (tokenizer.countTokens() < 2) {
                break;
            }
            int lower = Integer.parseInt(tokenizer.nextToken());
            int upper = Integer.parseInt(tokenizer.nextToken());
            if (lower > upper) {
                continue;
            }
            out.println("Case " + linecount + ":");
            for (int i = lower; i <= upper; i++) {
                String pt = "";
                if (i % 3 == 0)
                    pt += "Mercer";
                if (i % 4 == 0)
                    pt += "Bears";
                if (i % 18 == 0)
                    pt += "Grrrr";
                if (i % 33 == 0)
                    pt += "Bite";
                if (pt.length() > 0)
                    out.println(pt);
                else
                    out.println(i);
            }
            out.println();
            linecount++;
        }
        in.close();
        out.close();
    }
}