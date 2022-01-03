import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int mod = 998244353;
        boolean[] input = new boolean[n];
        String s = in.readLine();
        int[] prefix = new int[n];
        int[][] ncr = new int[n + 1][n + 1];
        ncr[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                ncr[i + 1][j] += ncr[i][j];
                ncr[i + 1][j] %= mod;
                ncr[i + 1][j + 1] += ncr[i][j];
                ncr[i + 1][j + 1] %= mod;
            }
        }
        for (int i = 0; i < ncr.length; i++) {
            // System.out.println(Arrays.toString(ncr[i]));
        }
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '1')
                input[i] = true;
            prefix[i] = input[i] ? 1 : 0;
            if (i > 0)
                prefix[i] += prefix[i - 1];
        }
        int answer = 1;
        if (prefix[n - 1] >= k) {
            for (int i = 0; i < n; i++) {
                int pre = i > 0 ? prefix[i - 1] : 0;
                for (int j = i + 1; j < n; j++) {
                    if (prefix[j] > pre + k)
                        continue;
                    int cnt1 = prefix[j] - pre;
                    int cnt0 = j - i + 1 - cnt1;
                    if (input[i]) {
                        cnt0--;
                    } else {
                        cnt1--;
                    }
                    if (input[j]) {
                        cnt0--;
                    } else {
                        cnt1--;
                    }
                    if (cnt0 < 0 || cnt1 < 0)
                        continue;
                    answer += ncr[cnt1 + cnt0][cnt0];
                    answer %= mod;
                }
            }

        }

        System.out.println(answer);
        in.close();
        out.close();
    }
}