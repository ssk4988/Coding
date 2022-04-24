import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        String s = in.readLine();
        StringBuilder b = new StringBuilder();
        boolean[] left = new boolean[n - 1];
        for (int i = 0; i < s.length(); i++) {
            left[i] = s.charAt(i) == 'L';
        }
        ArrayList<Boolean> type = new ArrayList<>();
        ArrayList<Integer> length = new ArrayList<>();
        int ind = 0;
        while (ind < left.length) {
            int start = ind;
            while (ind + 1 < left.length && left[ind + 1] == left[start]) {
                ind++;
            }
            type.add(left[start]);
            length.add(ind - start + 1);
            ind++;
        }
        TreeSet<Integer> unused = new TreeSet<>();
        for (int i = 1; i <= n; i++) {
            unused.add(i);
        }
        int curr = 1;
        int numused = 0;
        if (left[0]) {
            curr = length.get(0) + 1;
        } else {
            // curr = 1;
        }
        ind = 0;
        while (unused.size() > 0) {

            if (unused.size() == 1) {
                int f = unused.first();
                b.append(f + "\n");
                unused.remove(f);
                break;
            }
            int cnt = length.get(ind);
            boolean l = type.get(ind);
            if (l) {
                int val = unused.first();
                for (int i = 0; i < cnt - 1; i++) {
                    val = unused.higher(val);
                }
                b.append(curr + "\n");
                unused.remove(curr);
                curr = val;
                for (int i = 0; i < cnt - 1; i++) {
                    b.append(curr + "\n");
                    unused.remove(curr);
                    curr = unused.lower(curr);

                }
            } else {
                if (ind + 1 < type.size()) {
                    for (int i = 0; i < cnt; i++) {
                        b.append(curr + "\n");
                        unused.remove(curr);
                        curr = unused.higher(curr);
                    }
                    int lcnt = length.get(ind + 1);
                    for (int i = 0; i < lcnt; i++) {
                        curr = unused.higher(curr);
                    }
                    
                } else {
                    for (int i = 0; i < cnt; i++) {
                        b.append(curr + "\n");
                        unused.remove(curr);
                        curr = unused.higher(curr);
                    }
                }
            }
            ind++;
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}