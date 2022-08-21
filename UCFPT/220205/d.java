import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int a = Integer.parseInt(tokenizer.nextToken());
        int b = Integer.parseInt(tokenizer.nextToken());
        int cost2 = 0;
        while (a > b) {
            if (a % 2 == 1) {
                a++;
                cost2++;
            }
            cost2++;
            a /= 2;
        }
        cost2 += b - a;
        System.out.println(cost2);

        in.close();
        out.close();
    }
}