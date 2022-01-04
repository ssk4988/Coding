import java.io.*;
import java.util.*;

public class c {
    public static BufferedReader in;

    public static void main(String[] args) throws Exception {
        in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[] p = new int[n];
            Arrays.fill(p, -1);
            for (int i = 0; i < n; i++) {
                if (p[i] != -1)
                    continue;
                ArrayList<Integer> cycle = new ArrayList<>();
                cycle.add(query(i));
                while (true) {
                    int q = query(i);
                    if (cycle.get(0) == q)
                        break;
                    cycle.add(q);
                }
                for (int j = 0; j < cycle.size() - 1; j++) {
                    p[cycle.get(j)] = cycle.get(j + 1);
                }
                p[cycle.get(cycle.size() - 1)] = cycle.get(0);
                // System.out.println(Arrays.toString(p));
            }
            StringBuilder b = new StringBuilder();
            b.append("! ");
            for (int i = 0; i < n; i++) {
                b.append((p[i] + 1) + (i < n - 1 ? " " : "\n"));
            }
            System.out.print(b);
            System.out.flush();
        }
        in.close();
        out.close();
    }

    public static int query(int i) throws Exception {
        System.out.println("? " + (i + 1));
        System.out.flush();
        int k = Integer.parseInt(in.readLine());
        return k - 1;
    }
}