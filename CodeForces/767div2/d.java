import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            Set<String> set = new HashSet<>();
            boolean works = false;
            search: for (int i = 0; i < n; i++) {
                String s = in.readLine();
                if(works) continue;
                if (isPal(s)) {
                    works = true;
                }
                String invS = new StringBuilder(s).reverse().toString();
                if (set.contains(invS)) {
                    works = true;
                }
                if (s.length() == 2 && set.contains(invS + '#')) {
                    works = true;
                }
                if (s.length() == 3 && set.contains(invS.substring(0, 2))) {
                    works = true;
                }
                set.add(s);
                if (s.length() == 3) {
                    set.add(s.substring(0, 2) + '#');
                }
            }
            if (works) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
        in.close();
        out.close();
    }

    public static boolean isPal(String s) {
        if (s.length() == 1)
            return true;
        if (s.charAt(0) == s.charAt(s.length() - 1))
            return true;
        return false;
    }
}