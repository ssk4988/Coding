import java.io.*;
import java.util.*;

public class p003 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] n = new int[3];
        for (int i = 0; i < n.length; i++) {
            n[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int[] s = new int[3];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < s.length; i++) {
            s[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int m = (n[0] + n[1] + n[2]) / 2;
        int[] c = new int[m];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < c.length; i++) {
            c[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(c);
        int low = 0;
        int high = 2001 * 100000;
        while (low < high) {
            int mid = low + (high - low + 1) / 2;
            boolean works = true;
            int[] n2 = Arrays.copyOf(n, n.length);
            int[] s2 = Arrays.copyOf(s, s.length);
            int[] c2 = Arrays.copyOf(c, c.length);
            for (int i = 0; i < c2.length; i++) {
                int minS = Integer.MAX_VALUE;
                int minJ = -1;
                int minK = -1;
                for (int j = 0; j < n2.length; j++) {
                    for (int k = j; k < n2.length; k++) {
                        n2[j]--;
                        n2[k]--;
                        if (n2[j] >= 0 && n2[k] >= 0 && (c2[i] * (s2[j] + s2[k]) >= mid) && (s2[j] + s2[k]) < minS) {
                            minS = s2[j] + s2[k];
                            minJ = j;
                            minK = k;
                        }
                        n2[j]++;
                        n2[k]++;
                    }
                }
                if (minS == Integer.MAX_VALUE) {
                    works = false;
                    break;
                }
                n2[minJ]--;
                n2[minK]--;
            }
            if (works) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        System.out.println(low);
        in.close();
    }
}