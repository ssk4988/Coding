import java.io.*;
import java.util.*;

public class p064 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        StringBuilder b = new StringBuilder();
        b.append((n / 2 + m / 2) + "\n");
        for (int i = 2; i <= n; i += 2) {
            b.append(i + " " + 1 + " " + i + " " + m + "\n");
        }
        for (int i = 2; i <= m; i += 2) {
            b.append(1 + " " + i + " " + n + " " + i + "\n");
        }
        System.out.print(b);
        in.close();
    }
}