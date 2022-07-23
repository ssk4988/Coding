import java.io.*;
import java.util.*;

public class arithmetic {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int num = Integer.parseInt(tokenizer.nextToken());
            int sum = Integer.parseInt(tokenizer.nextToken());
            if (sum % num == 0) {
                StringBuilder b = new StringBuilder();
                for (int j = 0; j < num; j++) {
                    b.append(sum/num + (j < num - 1 ? " " : "\n"));
                }
                System.out.print(b);
            } else if (num % 2 == 0 && (2 * sum) % num == 0) {StringBuilder b = new StringBuilder();
                for (int j = 0; j < num; j++) {
                    b.append((sum / num - (num/2-1) + j) + (j < num - 1 ? " " : "\n"));
                }
                System.out.print(b);
            } else {
                System.out.println("IMPOSSIBLE");
            }
        }

        in.close();
        out.close();
    }
}