import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            int d = 2;
            b.append(d + "\n");
            int a = 1;
            boolean[] used = new boolean[n + 1];
            while (a <= n) {
                b.append(a == 1 ? a : (" " + a));
                used[a] = true;
                a *= d;
            }
            for (int i = 1; i < used.length; i++) {
                a = i;
                while (a < used.length && !used[a]) {
                    b.append(" " + a);
                    used[a] = true;
                    a *= 2;
                }
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
    }
}