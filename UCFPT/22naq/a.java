import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        long val = Long.parseLong(in.readLine());
        boolean[] used = new boolean[10];
        String s = val + "";
        for (int i = 0; i < s.length(); i++) {
            used[s.charAt(i) - '0'] = true;
        }
        TreeSet<Integer> left = new TreeSet<>();
        for (int i = 0; i < used.length; i++) {
            if (!used[i]) {
                left.add(i);
            }
        }

        if (left.size() == 0) {
            System.out.println("Impossible");
        } else {
            long h = Long.MAX_VALUE;
            long l = Long.MIN_VALUE;
            String lstr = "";
            String hstr = "";
            if (left.last() > 0) {
                while (lstr.length() + 1 < s.length()) {
                    lstr += left.last();
                }
                if (lstr.length() > 0) {
                    l = Math.max(Long.parseLong(lstr), l);
                }

            }
            if (left.first() > 0 || (left.higher(left.first()) != null)) {
                hstr += (left.first() == 0 ? left.higher(left.first()) : left.first());
                while (hstr.length() - 1 < s.length()) {
                    hstr += left.first();
                }
                if (hstr.length() > 0) {
                    h = Math.min(Long.parseLong(hstr), h);
                }
            }

            if (left.higher(s.charAt(0) - '0') != null) { // can make higher
                hstr = "" + left.higher(s.charAt(0) - '0');
                while (hstr.length() < s.length()) {
                    hstr += left.first();
                }
                h = Math.min(Long.parseLong(hstr), h);
            }

            if (left.lower(s.charAt(0) - '0') != null) {
                lstr = "" + left.lower(s.charAt(0) - '0');
                while (lstr.length() < s.length()) {
                    lstr += left.last();
                }
                l = Math.max(Long.parseLong(lstr), l);
            }
            //System.out.println(l + " " + h);
            if (h == Long.MAX_VALUE) {
                System.out.println(l);
            } else if (l < 0) {
                System.out.println(h);
            } else if (val - l == h - val) {
                System.out.println(l + " " + h);
            } else if (val - l < h - val) {
                System.out.println(l);
            } else {
                System.out.println(h);
            }
        }
        in.close();
        out.close();
    }
}