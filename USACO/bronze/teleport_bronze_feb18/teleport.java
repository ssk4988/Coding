/*
ID: ssk49881
LANG: JAVA
TASK: teleport
*/

import java.io.*;
import java.util.*;

public class teleport {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("teleport.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("teleport.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int start = Integer.parseInt(tokenizer.nextToken());
        int end = Integer.parseInt(tokenizer.nextToken());
        int x = Integer.parseInt(tokenizer.nextToken());
        int y = Integer.parseInt(tokenizer.nextToken());

        int d1 = Math.abs(end - start);
        int d2 = Math.abs(x - start) + Math.abs(end - y);
        int d3 = Math.abs(y - start) + Math.abs(end - x);
        int answer = Math.min(Math.min(d1, d2), d3);
        out.println(answer);

        in.close();
        out.close();
    }
}