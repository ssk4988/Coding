/*
ID: ssk49881
LANG: JAVA
TASK: theatresquare
*/

import java.io.*;
import java.util.*;

public class theatresquare {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        long m = Integer.parseInt(tokenizer.nextToken());
        long n = Integer.parseInt(tokenizer.nextToken());
        long a = Integer.parseInt(tokenizer.nextToken());
        long ma = m % a != 0 ? m / a + 1 : m / a;
        long na = n % a != 0 ? n / a + 1 : n / a;
        System.out.println(na * ma);

        in.close();
        out.close();
    }
}