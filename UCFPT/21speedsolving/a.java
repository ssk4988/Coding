import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int t = Integer.parseInt(tokenizer.nextToken());
        HashSet<Integer> set = new HashSet<>();
        tokenizer = new StringTokenizer(in.readLine());
        boolean works = false;
        for (int i = 0; i < n; i++) {
            int k = Integer.parseInt(tokenizer.nextToken());
            int l = reverse(k);
            if (set.contains(t - k) || (l != -1 && set.contains(t - l))) {
                works = true;
                break;
            }
            set.add(k);
            if (l != -1) {
                set.add(l);
            }
        }
        System.out.println(works ? "YES" : "NO");

        in.close();
        out.close();
    }

    public static int reverse(int num) {
        boolean[] invertible = { true, true, true, false, false, true, true, false, true, true };
        int[] invert = { 0, 1, 2, -1, -1, 5, 9, -1, 8, 6 };
        ArrayList<Integer> digits = new ArrayList<>();
        int n2 = num;
        while (n2 > 0) {
            digits.add(n2 % 10);
            if (!invertible[n2 % 10])
                return -1;
            n2 /= 10;
        }
        int compose = 0;
        for (int i = 0; i < digits.size(); i++) {
            compose += digits.get(i);
            if (i + 1 < digits.size()) {
                compose *= 10;
            }
        }
        return compose;
    }
}