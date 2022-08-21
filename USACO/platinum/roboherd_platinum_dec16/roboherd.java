import java.io.*;
import java.util.*;

public class roboherd {
    public static int[][] c;
    public static int n;
    public static int k;
    public static long nFormed = 0;
    public static long savings = 0;

    public static void main(String[] args) throws Exception {
        FastScanner in = new FastScanner("roboherd.in");
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("roboherd.out")));


        n = in.nextInt();
        k = in.nextInt();
        long norm = 0;
        long low = 0;
        long high = 0;
        c = new int[n][];
        for (int i = 0; i < n; i++) {
            int m = in.nextInt();
            c[i] = new int[m];
            for (int j = 0; j < m; j++) {
                c[i][j] = in.nextInt();
            }
            Arrays.sort(c[i]);
            norm += c[i][0];
            for (int j = m - 1; j >= 0; j--) {
                c[i][j] -= c[i][0];
            }
            high += c[i][m - 1];
        }
        Arrays.sort(c, (o1, o2) -> {
            for (int i = 0; i < Math.min(o1.length, o2.length); i++) {
                if (o1[i] != o2[i])
                    return Integer.compare(o1[i], o2[i]);
            }
            return Integer.compare(o1.length, o2.length);
        });
        while (low < high) {
            long mid = low + (high - low) / 2;
            nFormed = 0;
            if (canForm(0, mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        calc(0, low);
        long ans = (low + norm) * k - savings;
        out.println(ans);
        out.close();
    }

    public static boolean canForm(int index, long budget) {
        if (budget < 0)
            return false;
        if (index == n || (c[index].length > 1 && c[index][1] > budget)) {
            nFormed++;
            return nFormed >= k;
        }
        for (int v : c[index]) {
            if (v > budget)
                break;
            if (canForm(index + 1, budget - v))
                return true;
        }

        return false;
    }

    public static void calc(int index, long budget) {
        if (0 > budget)
            return;
        if (index == n || (c[index].length > 1 && c[index][1] > budget)) {
            savings += budget;
            return;
        }
        for (int v : c[index]) {
            if (v > budget)
                break;
            calc(index + 1, budget - v);
        }
    }
}
class FastScanner {
    BufferedReader br;
    StringTokenizer st;

    public FastScanner(String s) {
        try {
            br = new BufferedReader(new FileReader(s));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public FastScanner() {
        br = new BufferedReader(new InputStreamReader(System.in));
    }

    String nextToken() {
        while (st == null || !st.hasMoreElements()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }

    int nextInt() {
        return Integer.parseInt(nextToken());
    }

    long nextLong() {
        return Long.parseLong(nextToken());
    }

    double nextDouble() {
        return Double.parseDouble(nextToken());
    }
}