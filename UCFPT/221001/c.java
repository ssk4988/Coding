import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] a = new int[n];
        int[] s = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(tokenizer.nextToken());
            s[i] = a[i];
        }
        Arrays.sort(s);
        Map<Integer, Integer> correct = new HashMap<>();
        for (int i = 0; i < s.length; i++) {
            correct.put(s[i], i);
        }
        int q = Integer.parseInt(in.readLine());
        int qindex = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == q) {
                qindex = i;
                break;
            }
        }
        int proper = correct.get(q);
        for (int i = 0; qindex != proper && i < n; i++) {
            while (qindex != proper && correct.get(a[i]) != i) {
                int tmp = a[i];
                int newind = correct.get(a[i]);
                if (newind == qindex) {
                    qindex = i;
                } else if (i == qindex) {
                    qindex = newind;
                }
                a[i] = a[newind];
                a[newind] = tmp;
            }

        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < n; i++) {
            b.append(a[i] + (i + 1 < n ? " " : "\n"));
        }
        System.out.print(b);
        in.close();
    }
}