/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int num = Integer.parseInt(in.readLine());
        for (int i = 0; i < num; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            long a = Long.parseLong(tokenizer.nextToken());
            long b = Long.parseLong(tokenizer.nextToken());
            if(a == 0 || b == 0){
                System.out.println(0);
                continue;
            }
            long a2 = Math.max(a, b);
            long b2 = Math.min(a, b);
            long c1 = Math.min((a2-b2)/2, Math.min(a2/3, b2/1));
            long c2 = Math.min((a2-c1*3)/2, (b2-c1)/2);
            System.out.println(c2 + c1);
        }

        in.close();
        out.close();
    }
}