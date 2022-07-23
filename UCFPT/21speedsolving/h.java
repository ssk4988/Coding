import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        long n = Integer.parseInt(tokenizer.nextToken());
        long h = Integer.parseInt(tokenizer.nextToken());
        long v = Integer.parseInt(tokenizer.nextToken());
        long answer = 4 * Math.max(n -h, h) * Math.max(n-v, v);
        System.out.println(answer);
        in.close();
        out.close();
    }
}