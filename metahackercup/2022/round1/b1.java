import java.io.*;
import java.util.*;

public class b1 {
    public static long mod = 1000000007;

    public static void main(String[] args) throws Exception {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("watering_well_chapter_2_input.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("b1_output.txt")));
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            long[][] c = new long[n][2];
            ArrayList<Integer>[] by = new ArrayList[2];
            Arrays.setAll(by, e -> new ArrayList<>());
            for (int i = 0; i < n; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < 2; j++) {
                    c[i][j] = Long.parseLong(tokenizer.nextToken());
                    by[j].add(i);
                }
            }
            for (int j = 0; j < 2; j++) {
                final int k = j;
                Collections.sort(by[j], (o1, o2) -> Long.compare(c[o1][k], c[o2][k]));
            }
            long[][][] prefLin = new long[2][2][n];
            long[][][] prefQ = new long[2][2][n];
            for (int j = 0; j < 2; j++) {
                for (int i = 1; i < n; i++) {
                    long diff = c[by[j].get(i)][j] - c[by[j].get(i - 1)][j];
                    prefLin[j][0][i] = mod(prefLin[j][0][i - 1] + mod(i * diff));
                    prefQ[j][0][i] = mod(
                            prefQ[j][0][i - 1] + mod(2 * diff * prefLin[j][0][i - 1]) + mod(i * mod(diff * diff)));
                }
                for (int i = n - 2; i >= 0; i--) {
                    long diff = c[by[j].get(i + 1)][j] - c[by[j].get(i)][j];
                    prefLin[j][1][i] = mod(prefLin[j][1][i + 1] + mod((n - 1 - i) * diff));
                    prefQ[j][1][i] = mod(
                            prefQ[j][1][i + 1] + mod(2 * diff * prefLin[j][1][i + 1])
                                    + mod((n - 1 - i) * mod(diff * diff)));
                }
            }

            long ans = 0;
            int q = Integer.parseInt(in.readLine());
            for (int i = 0; i < q; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < 2; j++) {
                    long v = Long.parseLong(tokenizer.nextToken());
                    int low = -1;
                    int high = n - 1;
                    while (low < high) {
                        int mid = low + (high - low + 1) / 2;
                        if (c[by[j].get(mid)][j] <= v) {
                            low = mid;
                        } else {
                            high = mid - 1;
                        }
                    }
                    if (low >= 0) {
                        long k = Math.abs(v - c[by[j].get(low)][j]);
                        ans = mod(ans + mod(
                                prefQ[j][0][low] + mod(2 * k * prefLin[j][0][low]) + mod((low + 1) * mod(k * k))));
                    }
                    low++;
                    if (low <= n - 1) {
                        long k = Math.abs(c[by[j].get(low)][j] - v);
                        ans = mod(ans
                                + mod(prefQ[j][1][low] + mod(2 * k * prefLin[j][1][low])
                                        + mod((n - low) * mod(k * k))));
                    }
                    // out.printf("%d\n", ans);
                }
            }
            out.printf("Case #%d: %d\n", (cn + 1), ans);
        }
        in.close();
        out.close();
    }

    public static long mod(long arg) {
        if (arg < mod)
            return arg;
        return arg % mod;
    }
}