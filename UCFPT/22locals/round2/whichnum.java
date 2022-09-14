import java.io.*;
import java.util.*;

public class whichnum {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        long n = Long.parseLong(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        long[] p = new long[k];
        for (int i = 0; i < k; i++) {
            p[i] = Long.parseLong(tokenizer.nextToken());
        }
        long low = 0;
        long high = Long.MAX_VALUE;
        while (low < high) {
            long mid = low + (high - low) / 2;
            long cnt = mid;
            long maxbit = 1 << k;
            for (long i = 1; i < maxbit; i++) {
                int set = 0;
                long prod = 1;
                for (int j = 0; j < k; j++) {
                    if ((i & (1 << j)) > 0) {
                        set++;
                        prod *= p[j];
                    }
                }
                if (set % 2 == 1) {
                    cnt -= mid / prod;
                } else {
                    cnt += mid / prod;
                }
            }
            if (cnt >= n) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        System.out.println(low);
    }
    //public static long test(long[] p, long val, )
}