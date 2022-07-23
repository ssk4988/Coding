/*
ID: ssk49881
LANG: JAVA
TASK: prob4
*/

import java.io.*;
import java.util.*;

public class prob4 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        Map<String, String> first = new HashMap<>();
        Map<String, String> last = new HashMap<>();
        for (int i = 0; i < 26; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String s1 = tokenizer.nextToken();
            String s2 = tokenizer.nextToken("").substring(1);
            first.put(s1, s2);
        }
        for (int i = 0; i < 26; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String s1 = tokenizer.nextToken();
            String s2 = tokenizer.nextToken("").substring(1);
            last.put(s1, s2);
        }
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String fName = tokenizer.nextToken();
            String lName = tokenizer.nextToken();
            String nName = first.get(fName.substring(0, 1)) + " " + last.get(lName.substring(0, 1));
            out.println(fName + " " + lName + " = " + nName);
        }
        in.close();
        out.close();
    }
}