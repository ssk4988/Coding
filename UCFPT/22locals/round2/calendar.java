import java.io.*;
import java.util.*;

public class calendar {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int d = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int y = Integer.parseInt(tokenizer.nextToken());
        int n = Integer.parseInt(tokenizer.nextToken()) - 1;
        tokenizer = new StringTokenizer(in.readLine());
        int d1 = Integer.parseInt(tokenizer.nextToken());
        int m1 = Integer.parseInt(tokenizer.nextToken());
        int y1 = Integer.parseInt(tokenizer.nextToken());
        int newD = n;
        newD += (y1 - y) * 360;
        newD += (m1 - m) * 30;
        newD += (d1 - d);
        newD %= 7;
        newD++;
        System.out.println(newD);
    }
}