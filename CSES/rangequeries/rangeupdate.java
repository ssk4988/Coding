/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class rangeupdate {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        long[] arr = new long[size + 1];
        long[] diff = new long[size + 1];
        long[] tree = new long[size + 1];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < size; i++) {
            arr[i + 1] = Long.parseLong(tokenizer.nextToken());
            diff[i + 1] = arr[i + 1] - arr[i];
        }
        // System.out.println(Arrays.toString(diff));
        for (int i = 1; i < tree.length; i++) {
            update(i, diff[i], size, tree);
        }
        // System.out.println(Arrays.toString(tree));
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int t = Integer.parseInt(tokenizer.nextToken());
            if (t == 1) {
                int i1 = Integer.parseInt(tokenizer.nextToken());
                int i2 = Integer.parseInt(tokenizer.nextToken());
                long di = Long.parseLong(tokenizer.nextToken());
                // System.out.println(i1 + " " + i2 + " " + arr[i1] + " " + di);
                diff[i1] += di;
                update(i1, di, size, tree);
                if (i2 + 1 < tree.length) {
                    diff[i2 + 1] -= di;
                    update(i2 + 1, -di, size, tree);
                }
            } else {
                int i1 = Integer.parseInt(tokenizer.nextToken());
                b.append(sum(i1, tree) + "\n");
                // System.out.println(sum(i2, tree) - sum(i1 - 1, tree));
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static long sum(int index, long[] tree) {
        long sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    public static void update(int index, long change, int size, long[] tree) {
        while (index <= size) {
            tree[index] += change;
            index += index & -index;
        }
    }
}