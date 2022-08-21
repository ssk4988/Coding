import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int maxNum = 200000;
        int[] cnt = new int[maxNum + 1];
        for (int i = 0; i < n; i++) {
            cnt[Integer.parseInt(in.readLine())]++;
        }
        long left = 0;
        long right = 0;

        for (int i = 0; i < cnt.length; i++) {
            right += i * cnt[i];
        }
        for (int i = 0; i < cnt.length; i++) {
            long rem = cnt[i] * i;
            if (cnt[i] % 2 == 0) {
                left += cnt[i] / 2 * i;
                right -= cnt[i] / 2 * i;
            } else {
                left += cnt[i] / 2 * i;
                right -= (cnt[i] / 2 + 1) * i;
            }
            if (left == right) {
                System.out.println(i);
                break;
            }
            
            if (cnt[i] % 2 == 0) {
                left += cnt[i] / 2 * i;
                right -= cnt[i] / 2 * i;
            } else {
                left += cnt[i] / 2 * i;
                right -= cnt[i] / 2 * i;
                left += i;
            }
        }

        in.close();
        out.close();
    }
}