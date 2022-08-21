import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int d = Integer.parseInt(tokenizer.nextToken());
        int[] f = new int[n + 5];
        int v = 0;
        int c = 0;
        for (int i = 2; i < f.length; i++) {
            f[i] = v;
            c++;
            if (c >= d - 1) {
                v++;
                c = 0;
            }
        }
        int[] cnt = new int[n+10];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            cnt[Integer.parseInt(tokenizer.nextToken())]++;
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += f[cnt[i]];
        }
        System.out.println(ans);
        in.close();
    }
}