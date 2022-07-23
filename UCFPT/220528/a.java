import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        boolean[] composite = new boolean[20001];
        composite[0] = composite[1] = true;
        for (int i = 2; i < composite.length; i++) {
            if (!composite[i]) {
                for (int j = i * 2; j < composite.length; j += i) {
                    composite[j] = true;
                }
            }
        }
        ArrayList<Integer>[] separable = new ArrayList[20001];
        for (int i = 0; i < separable.length; i++) {
            separable[i] = new ArrayList<>();
        }
        for (int i = 0; i * i < separable.length; i++) {
            int s1 = i * i;
            for (int j = 0; s1 + j * j < separable.length; j++) {
                separable[s1 + j * j].add(i);
                separable[s1 + j * j].add(j);
            }
        }
        int[] m1 = new int[] { 1, 1, -1, -1 };
        int[] m2 = new int[] { 1, -1, 1, -1 };
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            int q = x * x + y * y;
            boolean prime = q > 1;
            double dq = Math.sqrt(q);
            int[] x1 = new int[] { 1, 0, -1, 0, x, -y, -x, y };
            int[] y1 = new int[] { 0, 1, 0, -1, y, x, -y, -x };
            if (composite[q]) {
                find: for (int j = 2; j <= dq && prime; j++) {
                    if (q % j == 0 && separable[j].size() > 0 && separable[q / j].size() > 0) {
                        for (int k = 0; k + 1 < separable[j].size(); k += 2) {
                            for (int l = 0; l < m1.length; l++) {
                                int a = m1[l] * separable[j].get(k);
                                int b = m2[l] * separable[j].get(k + 1);
                                int r = a * a + b * b;
                                if (r > 0 && (a * x + b * y) % r == 0 && (a * y - b * x) % r == 0) {
                                    prime = false;
                                    break find;
                                }
                            }
                        }
                    }
                }
            }
            System.out.println(prime ? "P" : "C");
        }
        in.close();
    }
}