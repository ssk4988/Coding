import java.io.*;
import java.util.*;

public class pseudo {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int max = 1 << n;
        int ans = 0;
        check: for (int i = 0; i < max; i++) {
            boolean  cur = (i & 1) == 1;
            int f = 1;
            for (int j = 1; j < n; j++) {
                if (!(cur ^ ((i & (1 << j))>0))) {
                    f++;
                } else {
                    f = 1;
                    cur = (i & (1 << j)) > 0;
                }
                if (f > k)
                    continue check;
            }
            ans++;
            //System.out.println(i);
        }
        System.out.println(ans);
    }
}