import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[][] data = new int[2][n];
            for (int i = 0; i < 2; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < n; j++) {
                    data[i][j] = Integer.parseInt(tokenizer.nextToken());
                }
            }
            tuple m1 = null;
            tuple m2 = null;
            tuple[] t = new tuple[n];
            tuple[] t1 = new tuple[n];
            tuple[] t2 = new tuple[n];
            for (int i = 0; i < n; i++) {
                t[i] = t2[i] = t1[i] = new tuple(i, data[0][i], data[1][i]);
                if (m1 == null || t[i].first > m1.first)
                    m1 = t[i];
                if (m2 == null || t[i].second > m2.second)
                    m2 = t[i];
            }
            Arrays.sort(t1, new comp1());
            Arrays.sort(t2, new comp2());
            for (int i = 0; i < t1.length; i++) {
                t1[i].a1 = i;
                t2[i].a2 = i;
            }
            int i1 = m1.a1;
            int i2 = m2.a2;
            LinkedList<Integer> l1 = new LinkedList<>();
            LinkedList<Integer> l2 = new LinkedList<>();
            l1.addFirst(m1.a1);
            l2.addFirst(m2.a2);
            l1.addFirst(m2.a1);
            l2.addFirst(m1.a2);
            while (l1.get(0) < l1.get(1) || l2.get(0) < l2.get(1)) {
                i1 = l1.get(0);
                i2 = l1.get(1);
                int mindex = l2.get(0);
                for (int i = i1; i <= i2; i++) {
                    mindex = Math.min(mindex, t1[i].a2);
                }
                i1 = l2.get(0);
                i2 = l2.get(1);
                l2.addFirst(mindex);
                mindex = l1.get(0);
                for (int i = i1; i <= i2; i++) {
                    mindex = Math.min(mindex, t2[i].a1);
                }
                l1.addFirst(mindex);
            }
            // System.out.println("case " + casenum);
            // System.out.println("min 1: " + t1[l1.get(0)].first + " min 2: " +
            // t2[l2.get(0)].second);
            int min1 = t1[l1.get(0)].first;
            int min2 = t2[l2.get(0)].second;
            for (int i = 0; i < t.length; i++) {
                b.append(t[i].first >= min1 || t[i].second >= min2 ? 1 : 0);
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static class comp1 implements Comparator<tuple> {
        @Override
        public int compare(c.tuple o1, c.tuple o2) {
            return o1.first - o2.first;
        }
    }

    public static class comp2 implements Comparator<tuple> {
        @Override
        public int compare(c.tuple o1, c.tuple o2) {
            return o1.second - o2.second;
        }
    }

    public static class tuple {
        int id;
        int first;
        int second;
        int a1;
        int a2;

        @Override
        public String toString() {
            return this.id + " " + first + " " + second + " " + a1 + " " + a2;
        }

        public tuple(int id, int first, int second) {
            this.id = id;
            this.first = first;
            this.second = second;
        }
    }
}