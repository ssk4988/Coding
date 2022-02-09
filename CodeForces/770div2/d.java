import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[] usefulness = new int[n];
            TreeSet<Integer> use = new TreeSet<>();
            TreeSet<Integer> elim = new TreeSet<>();
            for (int i = 0; i < n; i++) {
                use.add(i);
            }
            while (use.size() >= 3) {
                int[] q = new int[4];
                int[] qs = new int[4];
                q[0] = use.first();
                q[1] = use.higher(q[0]);
                q[2] = use.higher(q[1]);
                q[3] = use.higher(q[2]) == null ? elim.first() : use.higher(q[2]);
                int[][] inp = new int[4][3];
                for (int i = 0; i < 4; i++) {
                    int cnt = 0;
                    for (int j = 0; j < 4; j++) {
                        if (i == j)
                            continue;
                        inp[i][cnt] = q[j];
                        cnt++;
                    }
                    qs[i] = query(inp[i], in);
                }
                int max = Math.max(Math.max(qs[0], qs[1]), Math.max(qs[2], qs[3]));
                int maxcnt = 0;
                for (int i : qs) {
                    if (i == max)
                        maxcnt++;
                }
                if (maxcnt == 4) {
                    for (int k : q) {
                        use.remove(k);
                        elim.add(k);
                    }
                } else if (maxcnt == 3) {
                    int not = 0;
                    for (int i = 0; i < qs.length; i++) {
                        if (qs[i] != max) {
                            not = i;
                        }
                    }
                    for (int i : inp[not]) {
                        use.remove(i);
                        elim.add(i);
                    }
                } else if (maxcnt == 2) {
                    Set<Integer> set = new HashSet<>();
                    for (int i = 0; i < inp.length; i++) {
                        if (qs[i] == max) {
                            if (set.size() == 0) {
                                for (int k : inp[i]) {
                                    set.add(k);
                                }
                            } else {
                                Set<Integer> set2 = new HashSet<>();
                                for (int k : inp[i]) {
                                    set2.add(k);
                                }
                                set.retainAll(set2);
                            }
                        }
                    }
                    for (int i : q) {
                        if (!set.contains(i)) {
                            use.remove(i);
                            elim.add(i);
                        }
                    }
                }
            }
            System.out.println("! " + (use.first() + 1) + " " + (use.last() + 1));
        }

        in.close();
        out.close();
    }

    public static int query(int[] q, BufferedReader in) throws Exception {
        System.out.println("? " + (q[0] + 1) + " " + (q[1] + 1) + " " + (q[2] + 1));
        System.out.flush();
        int answer = Integer.parseInt(in.readLine());
        return answer;
    }
}