import java.io.*;
import java.util.*;

public class hotelqueries {
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
        Arrays.fill(tree, Long.MIN_VALUE);
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < size; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken());
            update(tree, i, arr[i]);
        }
        tokenizer = new StringTokenizer(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            int t = Integer.parseInt(tokenizer.nextToken());
            int index = indexMax(tree, t);
            b.append(index + 1);
            if (i < numQueries - 1)
                b.append(" ");
        }
        System.out.println(b);

        in.close();
        out.close();
    }

    public static int indexMax(long[] tree, int t) {
        int size = tree.length / 2;
        int start = 1;
        if (tree[start] < t)
            return -1;
        while (2 * start < tree.length) {
            if (tree[2 * start] >= t)
                start = 2 * start;
            else if (tree[2 * start + 1] >= t)
                start = 2 * start + 1;
            else {
                start = -1;
                break;
            }
        }
        if (start >= size) {
            update(tree, start - size, tree[start] - t);
            return start - size;
        }
        return start;
    }

    public static long maximum(long[] tree, int i1, int i2) {
        int size = tree.length / 2;
        i1 += size;
        i2 += size;
        long max = Long.MAX_VALUE;
        while (i1 <= i2) {
            if (i1 % 2 == 1)
                max = Math.max(max, tree[i1++]);
            if (i2 % 2 == 0)
                max = Math.max(max, tree[i2--]);
            i1 /= 2;
            i2 /= 2;
        }
        return max;
    }

    public static void update(long[] tree, int index, long value) {
        int size = tree.length / 2;
        index += size;
        tree[index] = value;
        for (index /= 2; index >= 1; index /= 2) {
            tree[index] = Math.max(tree[2 * index], tree[2 * index + 1]);
        }
    }
}