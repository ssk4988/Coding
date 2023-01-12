import java.io.*;
import java.util.*;

public class D1762 {
    static final Random random = new Random();
    static int[] start;

    public static void ruffle(int[] a) {
        int n = a.length;
        for (int i = 0; i < n; i++) {
            int oi = random.nextInt(n), temp = (int) a[oi];
            a[oi] = a[i];
            a[i] = temp;
        }
    }

    static int query(int a, int b) {
        return getGcd(start[a], start[b]);
    }

    static int getGcd(int a, int b) {
        if (a == 0)
            return b;
        if (b == 0)
            return a;
        return gcd(a, b);
    }

    static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int n = Integer.parseInt(in.readLine());
        start = new int[n];
        for (int i = 0; i < n; i++) {
            start[i] = i;
        }
        Map<Integer, Integer> freq = new HashMap<>();
        for (int i = 0; i < 5000; i++) {
            int[] arr = new int[n];
            for (int j = 0; j < n; j++) {
                arr[j] = j;
            }
            ruffle(arr);
            int[] to = new int[n];
            int[] from = new int[n];
            for (int j = 0; j < n; j++) {
                to[arr[j]] = start[j];
                from[start[j]] = arr[j];
            }
            int[][] gcds = new int[n][2];
            for (int j = 0; j < n; j++) {
                int a1 = (j) % n, a2 = (j + 1) % n;
                int l = query(start[arr[a1]], start[arr[a2]]);
                gcds[a1][0] = l;
                gcds[a2][1] = l;
            }
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (gcds[j][0] == gcds[j][1]) {
                    cnt++;
                }
            }
            if (cnt == 1) {
                System.out.println(Arrays.toString(arr));
                System.out.println(Arrays.toString(to));
            }
            if (!freq.containsKey(cnt)) {
                freq.put(cnt, 0);
            }
            freq.put(cnt, freq.get(cnt) + 1);
        }
        for (int i : freq.keySet()) {
            b.append(i + " " + freq.get(i) + "\n");
        }
        System.out.print(b);
        in.close();
    }
}