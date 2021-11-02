/*
ID: ssk49881
LANG: JAVA
TASK: billboard
*/

import java.io.*;
import java.util.*;

public class billboard {
    public static void main(String[] args) throws Exception {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("billboard.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("billboard.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int x11 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int y11 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int x21 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int y21 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        tokenizer = new StringTokenizer(in.readLine());
        int x12 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int y12 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int x22 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int y22 = Integer.parseInt(tokenizer.nextToken()) + 2000;
        int width = x21 - x11;
        int height = y21 - y11;
        int interx = Math.min(x22, x21) - Math.max(x12, x11);
        interx = Math.max(interx, 0);
        int intery = Math.min(y22, y21) - Math.max(y12, y11);
        intery = Math.max(intery, 0);
        int bx = height - intery == 0 && (Math.min(x22, x21) >= x21 || Math.max(x12, x11) <= x11) ? width - interx
                : width;
        int by = width - interx == 0 && (Math.min(y22, y21) >= y21 || Math.max(y12, y11) <= y11) ? height - intery
                : height;
        out.println(bx * by);

        in.close();
        out.close();
    }
}