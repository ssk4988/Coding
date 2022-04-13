import java.util.*;
import java.io.*;

public class addiply {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int length = Integer.parseInt(in.readLine());
        
        for (int i = 0; i < length; i ++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken());
            int c = Integer.parseInt(tokenizer.nextToken());
            b.append((a+c) + " " + (a*c) + "\n");
        }

        System.out.print(b);
        in.close();
    }
}