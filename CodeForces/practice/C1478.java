import java.io.*;
import java.util.*;

public class C1478 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            boolean works = true;
            int n = Integer.parseInt(in.readLine());
            long[] arr = new long[2 * n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            Map<Long, Integer> map = new HashMap<>();
            for (int i = 0; i < 2 * n; i++) {
                arr[i] = Long.parseLong(tokenizer.nextToken());
                if (!map.containsKey(arr[i]))
                    map.put(arr[i], 0);
                map.put(arr[i], map.get(arr[i]) + 1);
            }
            for (long l : map.keySet()) {
                if (l % 2 == 1 || map.get(l) != 2)
                    works = false;
            }
            Arrays.sort(arr);
            long difsum = 0;
            long running = 0;
            for (int i = 1; i < n && works; i++) {
                if ((arr[2 * (i)] - arr[2 * (i - 1)]) % (2 * i) != 0) {
                    works = false;
                    break;
                }
                running += (arr[2 * (i)] - arr[2 * (i - 1)]) / (2 * i);
                difsum += 2 * running;
            }
            long first = arr[0] - difsum;
            if (first <= 0 || first % (2 * n) != 0)
                works = false;
            if (works) {
                first /= (2 * n);
            }
            b.append(works ? "YES\n" : "NO\n");
        }

        System.out.print(b);
        in.close();
    }
}