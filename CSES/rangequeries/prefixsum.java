import java.io.*;
import java.util.*;

public class prefixsum {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int originalSize = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        int size = originalSize;
        while ((size & -size) != size)
            size += size & -size;
        long[] arr = new long[originalSize];
        long[] sumtree = new long[2 * size];
        long[] preftree = new long[2 * size];
        Arrays.fill(preftree, Long.MIN_VALUE);
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < originalSize; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken());
            sumupdate(sumtree, preftree, i, arr[i], size);
        }
        // printTree(sumtree);
        // printTree(maxtree);
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int t = Integer.parseInt(tokenizer.nextToken());
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken());
            if (t == 1) {
                arr[i1] = i2;
                sumupdate(sumtree, preftree, i1, i2, size);
            } else {
                i2--;
                b.append(max(preftree, sumtree, i1, i2, size) + "\n");
                // System.out.println("Max: " + maxIndex + " sum: " + s);
                // printTree(sumtree);
                // printTree(maxtree);
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static void printTree(long[] tree) {
        System.out.println("Tree:");
        for (int i = 1; i < tree.length; i *= 2) {
            for (int j = 0; j < i; j++) {
                System.out.print(tree[i + j] + " ");
            }
            System.out.println();
        }
    }

    public static long sum(long[] sumtree, int i1, int i2, int size) {
        i1 += size;
        i2 += size;
        long sum = 0;
        while (i1 <= i2) {
            if ((i1 & 1) == 1)
                sum += sumtree[i1++];
            if ((i2 & 1) == 0)
                sum += sumtree[i2--];
            i1 >>= 1;
            i2 >>= 1;
        }
        return sum;
    }

    public static long max(long[] preftree, long[] sumtree, int i1, int i2, int size) {
        long lsum = 0;
        long rsum = sum(sumtree, i1, i2, size);
        long max = Math.max(lsum, rsum);
        i1 += size;
        i2 += size;
        while (i1 <= i2) {
            if ((i1 & 1) == 1) {
                max = Math.max(max, lsum + preftree[i1]);
                lsum += sumtree[i1++];
            }
            if ((i2 & 1) == 0) {
                rsum -= sumtree[i2];
                max = Math.max(max, rsum + preftree[i2--]);
            }
            i1 >>= 1;
            i2 >>= 1;
        }
        return max;
    }

    public static void sumupdate(long[] sumtree, long[] preftree, int index, long value, int size) {
        index += size;
        preftree[index] = sumtree[index] = value;
        for (index >>= 1; index >= 1; index >>= 1) {
            sumtree[index] = sumtree[2 * index] + sumtree[2 * index + 1];
            preftree[index] = Math.max(preftree[2 * index], sumtree[2 * index] + preftree[2 * index + 1]);
        }
    }
}