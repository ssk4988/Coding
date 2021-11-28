import java.io.*;
import java.util.*;

public class dynamicminimum {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        int size2 = size;
        while ((size2 & -size2) != size2)
            size2 += size2 & -size2;
        long[] arr = new long[size];
        long[] tree = new long[2 * size2];
        Arrays.fill(tree, Long.MAX_VALUE);
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < size; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken());
            update(tree, i, arr[i], size2);
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int t = Integer.parseInt(tokenizer.nextToken());
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken());
            if (t == 1) {
                // System.out.println(i1 + " " + i2 + " " + arr[i1] + " " + di);
                arr[i1] = i2;
                update(tree, i1, i2, size2);
            } else {
                b.append(minimum(tree, i1, i2 - 1, size2) + "\n");
                // System.out.println(sum(i2, tree) - sum(i1 - 1, tree));
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static long minimum(long[] tree, int i1, int i2, int size) {
        i1 += size;
        i2 += size;
        long min = Long.MAX_VALUE;
        while (i1 <= i2) {
            if (i1 / 2 * 2 != i1)
                min = Math.min(min, tree[i1++]);
            if (i2 / 2 * 2 == i2)
                min = Math.min(min, tree[i2--]);
            i1 /= 2;
            i2 /= 2;
        }
        return min;
    }

    public static void update(long[] tree, int index, long value, int size) {
        index += size;
        tree[index] = value;
        for (index /= 2; index >= 1; index /= 2) {
            tree[index] = Math.min(tree[2 * index], tree[2 * index + 1]);
        }
    }
}