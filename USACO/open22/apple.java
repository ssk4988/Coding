import java.io.*;
import java.util.*;

public class apple {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        ArrayList<c> cows = new ArrayList<>();
        ArrayList<c> apples = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int q = Integer.parseInt(tokenizer.nextToken());
            int t = Integer.parseInt(tokenizer.nextToken());
            int p = Integer.parseInt(tokenizer.nextToken());
            int n1 = Integer.parseInt(tokenizer.nextToken());
            c c1 = new c(t + p, t - p, n1);
            if (q == 1) {
                cows.add(c1);
            } else {
                apples.add(c1);
            }
        }
        Collections.sort(cows, new cc());
        Collections.sort(apples, new cc());
        TreeSet<c> cur = new TreeSet<>((o1, o2) -> {
            if (o1.x == o2.x)
                return o1.y - o2.y;
            return o1.x - o2.x;
        });
        int ans = 0;
        int index = 0;
        for (c a : apples) {
            while (index < cows.size() && cows.get(index).y <= a.y) {
                cur.add(cows.get(index));
                index++;
            }
            c s = new c(a.x, a.y + 1, 0);
            c c1 = cur.floor(s);
            while (c1 != null && a.amt > 0) {
                int take = Math.min(a.amt, c1.amt);
                ans += take;
                a.amt -= take;
                c1.amt -= take;
                if (c1.amt <= 0)
                    cur.remove(c1);
                c1 = cur.floor(s);
            }
        }
        System.out.println(ans);

        in.close();
    }

    static class cc implements Comparator<c> {
        @Override
        public int compare(apple.c o1, apple.c o2) {
            if (o1.y == o2.y)
                return o1.x - o2.x;
            return o1.y - o2.y;
        }
    }

    static class c {
        int x, y, amt;

        public c(int x, int y, int amt) {
            this.x = x;
            this.y = y;
            this.amt = amt;
        }
    }
}