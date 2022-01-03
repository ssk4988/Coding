import java.io.*;
import java.util.*;

public class conv {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        long[] numA = new long[m + 1];
        long[] numB = new long[m + 1];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken());
            int b = Integer.parseInt(tokenizer.nextToken());
            numA[a]++;
            numB[b]++;
        }
        // System.out.println(Arrays.toString(numA));
        // System.out.println(Arrays.toString(numB));
        long answer = 0;
        for (int k = 0; k <= 2 * m; k++) {
            int lower = Math.max(k - m, 0);
            int upper = Math.min(k, m);
            for (int i = lower; i <= upper; i++) {
                answer += numA[i] * numA[k - i];
            }
            if (k > 0) {
                lower = Math.max(k - m - 1, 0);
                upper = Math.min(k - 1, m);
                for (int i = lower; i <= upper; i++) {
                    answer -= numB[i] * numB[k - 1 - i];
                }
            }
            System.out.println(answer);
        }
        in.close();
    }
}