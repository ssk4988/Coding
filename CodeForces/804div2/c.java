import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        int mod = 1000000007;
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] perm = new int[n];
            int[] rperm = new int[n];
            for (int i = 0; i < n; i++) {
                perm[i] = Integer.parseInt(tokenizer.nextToken());
                rperm[perm[i]] = i;
            }
            long ans = 1;
            int low = rperm[0];
            int high = rperm[0];
            int mult = 0;
            for (int i = 1; i < n; i++) {
                if (rperm[i] < low || rperm[i] > high) {
                    if (rperm[i] < low) {
                        mult += low - rperm[i] - 1;
                        low = rperm[i];
                    } else {
                        mult += rperm[i] - high - 1;
                        high = rperm[i];
                    }
                } else {
                    ans *= mult;
                    ans %= mod;
                    mult--;
                }
            }
            b.append(ans + "\n");
        }
        System.out.print(b);
        in.close();
    }
}