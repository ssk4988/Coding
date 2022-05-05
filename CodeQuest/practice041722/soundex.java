import java.io.*;
import java.util.*;

public class soundex {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        int[] group = new int[] { 8, 1, 2, 3, 8, 1, 2, 7, 8, 2, 2, 4, 5, 5, 8, 1, 2, 6, 2, 3, 8, 1, 7, 2, 8, 2 };
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            TreeMap<String, Integer> map = new TreeMap<>();
            for (int i = 0; i < n; i++) {
                int start = 0;
                String s = in.readLine().toUpperCase();
                StringBuilder s2 = new StringBuilder();
                while (start + 1 < s.length() && group[s.charAt(start) - 'A'] > 6) {
                    s2.append(s.charAt(start));
                    start++;
                }

                s2.append(s.charAt(start));
                int ind = start;
                while (ind < s.length()) {
                    int ind2 = ind + 1;
                    while (ind2 < s.length() && (group[s.charAt(ind) - 'A'] == group[s.charAt(ind2) - 'A']
                            || group[s.charAt(ind2) - 'A'] == 7)) {
                        ind2++;
                    }
                    if (ind2 < s.length()) {
                        s2.append(s.charAt(ind2));
                    }
                    ind = ind2;
                }
                s = s2.toString();
                s2 = new StringBuilder();
                s2.append(s.charAt(0));
                for (int j = 1; j < s.length(); j++) {
                    if (group[s.charAt(j) - 'A'] > 6)
                        continue;
                    s2.append(s.charAt(j));
                }
                s = s2.toString();
                s2 = new StringBuilder();
                s2.append(s.charAt(0));
                for (int j = 1; j < s.length(); j++) {
                    if (s2.length() < 4) {
                        s2.append(group[s.charAt(j) - 'A']);
                    }
                }
                while (s2.length() < 4) {
                    s2.append(0);
                }
                s = s2.toString();
                if (!map.containsKey(s)) {
                    map.put(s, 0);
                }
                map.put(s, map.get(s) + 1);
            }
            b.append("OUTPUT\n");
            for (Map.Entry<String, Integer> e : map.entrySet()) {
                b.append(e.getKey() + " " + e.getValue() + "\n");
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}