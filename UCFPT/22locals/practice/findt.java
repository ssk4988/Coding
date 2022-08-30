import java.io.*;
import java.util.*;

public class findt {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int p = Integer.parseInt(in.readLine());
        long[][] c = new long[p][2];
        TreeSet<long[]> set = new TreeSet<>((o1, o2) -> {
            if (o1[0] == o2[0]) {
                return Long.compare(o1[1], o2[1]);
            }
            return Long.compare(o1[0], o2[0]);
        });
        for (int i = 0; i < p; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            c[i][0] = 2 * parse(tokenizer.nextToken());
            c[i][1] = 2 * parse(tokenizer.nextToken());
            set.add(new long[] { c[i][0], c[i][1] });
        }
        long ans = 0;
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < i; j++) {
                long dx1 = c[i][0] - c[j][0];
                long dy1 = c[i][1] - c[j][1];
                long[] mid = new long[] { (c[i][0] + c[j][0]) / 2, (c[i][1] + c[j][1]) / 2 };
                if (!set.contains(mid))
                    continue;
                long[][] nc = new long[2][2];
                nc[0][0] = mid[0] + dy1;
                nc[0][1] = mid[1] - dx1;
                nc[1][0] = mid[0] - dy1;
                nc[1][1] = mid[1] + dx1;
                if (set.contains(nc[0]))
                    ans++;
                if (set.contains(nc[1]))
                    ans++;

            }
        }
        System.out.println(ans);
        in.close();
    }

    public static long parse(String s) {
        if (s.indexOf('.') == -1) {
            return Long.parseLong(s) * 1000;
        }
        int k = s.indexOf('.');
        String s1 = s.substring(k + 1);
        while (s1.length() < 3)
            s1 += "0";
        s = s.substring(0, k) + s1;
        return Long.parseLong(s);
    }
}
