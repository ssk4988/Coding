/*
ID: ssk49881
LANG: JAVA
TASK: billboard
*/

import java.io.*;
import java.util.*;
import java.awt.*;

public class billboard {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("billboard.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("billboard.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int x1 = Integer.parseInt(tokenizer.nextToken());
        int y1 = Integer.parseInt(tokenizer.nextToken());
        int x2 = Integer.parseInt(tokenizer.nextToken());
        int y2 = Integer.parseInt(tokenizer.nextToken());
        Rectangle r1 = new Rectangle(x1, -y2, x2 - x1, y2 - y1);
        tokenizer = new StringTokenizer(in.readLine());
        x1 = Integer.parseInt(tokenizer.nextToken());
        y1 = Integer.parseInt(tokenizer.nextToken());
        x2 = Integer.parseInt(tokenizer.nextToken());
        y2 = Integer.parseInt(tokenizer.nextToken());
        Rectangle r2 = new Rectangle(x1, -y2, x2 - x1, y2 - y1);
        tokenizer = new StringTokenizer(in.readLine());
        x1 = Integer.parseInt(tokenizer.nextToken());
        y1 = Integer.parseInt(tokenizer.nextToken());
        x2 = Integer.parseInt(tokenizer.nextToken());
        y2 = Integer.parseInt(tokenizer.nextToken());
        Rectangle r3 = new Rectangle(x1, -y2, x2 - x1, y2 - y1);
        out.println(area(r1) + area(r2) - area(r1.intersection(r3)) - area(r2.intersection(r3)));

        in.close();
        out.close();
    }

    public static long area(Rectangle r) {
        return r.isEmpty() ? 0 : (long) r.getHeight() * (long) r.getWidth();
    }
}