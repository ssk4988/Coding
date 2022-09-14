import java.io.*;
import java.util.*;

public class house {
    public static long[] bit;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        bit = new long[n + 10];
        for (int i = 0; i < n; i++) {
            int v = Integer.parseInt(in.readLine());
            update(i + 1, v);
        }
        int q = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for (int i = 0; i < q; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());

            boolean type = tokenizer.nextToken().charAt(0) == 'R';
            int a = Integer.parseInt(tokenizer.nextToken());
            int b = Integer.parseInt(tokenizer.nextToken());
            if (type) {

                out.append(sum(b) - sum(a - 1));
                out.append("\n");
            } else {
                update(a, b);
            }
        }
        System.out.print(out);
    }

    public static void update(int ind, int val) {
        while (ind < bit.length) {
            bit[ind] += val;
            ind += ind & -ind;
        }
    }

    public static long sum(int ind) {
        long sum = 0;
        while (ind > 0) {
            sum += bit[ind];
            ind -= ind & -ind;
        }
        return sum;
    }
}