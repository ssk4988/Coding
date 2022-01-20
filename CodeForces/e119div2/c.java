import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder o = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            long x = Long.parseLong(tokenizer.nextToken());
            boolean[] arr = new boolean[n];
            String s = in.readLine();
            for (int i = 0; i < n; i++) {
                arr[i] = s.charAt(i) == '*';
            }
            ArrayList<Boolean> b = new ArrayList<>();
            ArrayList<Long> iList = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (i == 0 || (b.get(b.size() - 1) != arr[i])) {
                    b.add(arr[i]);
                    iList.add(1L);
                } else {
                    iList.set(iList.size() - 1, iList.get(iList.size() - 1) + 1);
                }

            }
            // System.out.println(b);
            //System.out.println("iList: " + iList);
            ArrayList<Long> l = new ArrayList<>();
            l.add(1L);
            for (int i = b.size() - 1; i >= 0; i--) {
                if (l.get(l.size() - 1) >= x) {
                    l.add(l.get(l.size() - 1) + 1);
                } else {
                    l.add((!b.get(i) ? 1 : iList.get(i) * k + 1) * l.get(l.size() - 1));
                }
            }
            // System.out.println("L: " + l);
            ArrayList<Long> v = new ArrayList<>();
            for (int i = 0; i < iList.size(); i++) {
                v.add(0L);
            }
            long y = x;
            for (int i = l.size() - 2; i >= 0; i--) {
                int index = iList.size() - 1 - (i);
                if (b.get(index)) {
                    long j = Math.min(y / l.get(i), 1 + k * iList.get(index));
                    v.set(index, Math.max(j - 1, 0));
                    y -= Math.max(j - 1, 0) * l.get(i);
                } else {
                    v.set(index, iList.get(index));
                }

            }
            // System.out.println(v);
            for (int i = 0; i < v.size(); i++) {
                for (int j = 0; j < v.get(i); j++) {
                    o.append(b.get(i) ? 'b' : 'a');
                }
            }
            o.append("\n");
        }
        System.out.print(o);
        in.close();
        out.close();
    }
}