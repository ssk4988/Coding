import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            int[] b = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            ArrayList<int[]> list = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                b[i] = Integer.parseInt(tokenizer.nextToken());
                list.add(new int[] { b[i] == 0 ? n : (i + 1) / b[i], Math.min(n, (i + 1) / (b[i] + 1) + 1), i });
            }
            Collections.sort(list, (o1, o2) -> {
                for (int i = 0; i < o1.length; i++) {
                    if (o1[i] != o2[i])
                        return o1[i] - o2[i];
                }
                return o1[o1.length - 1] - o2[o1.length - 1];
            });
            TreeSet<Integer> set = new TreeSet<>();
            for (int i = 1; i <= n; i++) {
                set.add(i);
            }
            int[] a = new int[n];
            for (int[] arr : list) {
                int k = set.higher(arr[1] - 1);
                set.remove(k);
                a[arr[2]] = k;
            }
            for (int i = 0; i < n; i++) {
                out.append(a[i] + (i + 1 < n ? " " : "\n"));
            }
        }
        System.out.print(out);
        in.close();
    }
}