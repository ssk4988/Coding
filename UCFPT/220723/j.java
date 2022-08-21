import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        TreeSet<Integer> comp = new TreeSet<>();
        Map<Integer, Integer> m = new HashMap<>();
        t[] ts = new t[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            ts[i] = new t(Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()));
            comp.add(ts[i].f);
            comp.add(ts[i].s);
        }
        int cnt = 0;
        for (int i : comp) {
            m.put(i, cnt++);
        }
        for (int i = 0; i < n; i++) {
            ts[i].f = m.get(ts[i].f);
            ts[i].s = m.get(ts[i].s);
        }

        Arrays.sort(ts, (o1, o2) -> {
            if (o1.f == o2.f) {
                if (o1.s > o2.s)
                    return 1;
                if (o1.s == o2.s)
                    return 0;
                return -1;
            }
            if (o1.f > o2.f)
                return 1;
            return -1;
        });
        long inv = 0;
        long[] bit = new long[2 * n + 20];
        for (int i = 0; i < n; i++) {
            inv += sum(bit, bit.length - 2) - sum(bit, ts[i].s);
            update(bit, ts[i].s, 1);
        }
        System.out.println(inv);

        in.close();
    }

    public static void update(long[] bit, int index, int value) {
        index++;
        while (index < bit.length) {
            bit[index] += value;
            index += index & -index;
        }
    }

    public static long sum(long[] bit, int index) {
        index++;
        long sum = 0;
        while (index > 0) {
            sum += bit[index];
            index -= index & -index;
        }
        return sum;
    }

    static class t {
        int f;
        int s;

        public t(int f, int s) {
            this.f = f;
            this.s = s;
        }
    }
}