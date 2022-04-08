import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            String s = in.readLine();
            int ops = 0;
            boolean[] conv = new boolean[n];
            boolean[] good = new boolean[n];
            for (int i = 0; i < n; i++) {
                conv[i] = s.charAt(i) == '(';
            }
            for (int i = 0; i < n; i++) {
                if (good[i])
                    continue;
                if (i + 1 < n) {
                    if (!(!conv[i] && conv[i + 1])) {
                        ops++;
                        good[i] = true;
                        good[i + 1] = true;
                    } else {
                        int k = i + 2;
                        while (k < n && conv[k]) {
                            k++;
                        }
                        if (k == n) {
                            break;
                        } else {
                            ops++;
                            for (int j = i; j <= k; j++) {
                                good[j] = true;
                            }
                            i = k;
                        }
                    }
                }
            }
            int left = 0;
            for (int i = n - 1; i >= 0; i--) {
                if (good[i]) {
                    break;
                }
                left++;
            }
            b.append(ops + " " + left + "\n");
        }
        System.out.print(b);
        in.close();
    }
}