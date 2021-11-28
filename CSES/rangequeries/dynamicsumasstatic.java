/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class dynamicsumasstatic {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        int[] arr = new int[size + 1];
        long[] tree = new long[size + 1];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < size; i++) {
            arr[i + 1] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 1; i < tree.length; i++) {
            update(i, arr[i], size, tree);
        }
        // System.out.println(Arrays.toString(tree));
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int i1 = Integer.parseInt(tokenizer.nextToken());
            int i2 = Integer.parseInt(tokenizer.nextToken());
            b.append(sum(i2, tree) - sum(i1 - 1, tree) + "\n");
            // System.out.println(sum(i2, tree) - sum(i1 - 1, tree));
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