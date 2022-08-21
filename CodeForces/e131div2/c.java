import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for (int c = 0; c < nc; c++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            int[] cnt = new int[n];
            int[] w = new int[m];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < m; i++) {
                w[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                cnt[w[i]]++;
            }
            TreeSet<worker> set = new TreeSet<>();
            for (int i = 0; i < cnt.length; i++) {
                set.add(new worker(i, cnt[i]));
            }
            while (set.size() > 1 && set.first().time + 2 < set.last().time) {
                worker w1 = set.first();
                worker w2 = set.last();
                set.remove(w1);
                set.remove(w2);
                w1.time += 2;
                w2.time--;
                set.add(w1);
                set.add(w2);
            }
            b.append(set.last().time + "\n");
        }
        System.out.print(b);
        in.close();
    }

    public static class worker implements Comparable<worker> {
        int id;
        int time = 0;

        public worker(int id, int time) {
            this.id = id;
            this.time = time;
        }

        @Override
        public int compareTo(c.worker o) {
            if (this.time == o.time)
                return this.id - o.id;
            return this.time - o.time;
        }

    }
}