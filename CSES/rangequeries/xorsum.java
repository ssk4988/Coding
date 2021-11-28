import java.io.*;
import java.util.*;

public class xorsum {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int length = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        long[] arr = new long[length];
        long[] prefix = new long[length + 1];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < length; i++) {
            arr[i] = Long.parseLong(tokenizer.nextToken());
            prefix[i + 1] ^= arr[i] ^ prefix[i];
            // System.out.print(prefix[i] + " ");
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int i1 = Integer.parseInt(tokenizer.nextToken());
            int i2 = Integer.parseInt(tokenizer.nextToken());
            b.append((prefix[i2] ^ prefix[i1 - 1]) + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}