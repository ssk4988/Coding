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
        long[] maxtree = new long[2 * size];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < originalSize; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken());
            sumupdate(maxtree, sumtree, i, arr[i], size);
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int t = Integer.parseInt(tokenizer.nextToken());
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken());
            if (t == 1) {
                arr[i1] = i2;
                sumupdate(maxtree, sumtree, i1, i2, size);
            } else {
                i2--;
                int maxIndex = max(maxtree, sumtree, i1, i2, size);
                long s = sum(sumtree, i1, maxIndex, size);
                b.append(s + "\n");
                System.out.println("Max: " + maxIndex + " sum: " + s);
                printTree(sumtree);
                printTree(maxtree);
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static void printTree(long[] tree) {
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

    public static int max(long[] maxtree, long[] sumtree, int i1, int i2, int size) {
        i1 += size;
        i2 += size;
        long max = Long.MIN_VALUE;
        int maxIndex = 0;
        while (i1 <= i2) {
            if ((i1 & 1) == 1) {
                long s = sum(sumtree, 0, i1, size);
                if (s > max) {
                    max = s;
                    maxIndex = i1;
                }
                i1++;
            }
            if ((i2 & 1) == 0) {
                long s = sum(sumtree, 0, i2, size);
                if (s > max) {
                    max = s;
                    maxIndex = i2;
                }
                i2--;
            }
            i1 >>= 1;
            i2 >>= 1;
        }
        return maxIndex - size;
    }

    public static void sumupdate(long[] maxtree, long[] sumtree, int index, long value, int size) {
        int index2 = index;
        index += size;
        sumtree[index] = value;
        for (index >>= 1; index >= 1; index >>= 1) {
            sumtree[index] = sumtree[2 * index] + sumtree[2 * index + 1];
        }
        maxupdate(maxtree, sumtree, index2, size);
    }

    public static void maxupdate(long[] maxtree, long[] sumtree, int index, int size) {
        index += size;
        for (index >>= 1; index >= 1; index >>= 1) {
            long prev = maxtree[index];
            if (sumtree[2 * index] > sumtree[2 * index] + sumtree[2 * index + 1]) {
                maxtree[index] = maxtree[2 * index];
            } else {
                maxtree[index] = maxtree[2 * index + 1];
            }
            if(prev != maxtree[index]){
                System.out.println("changed " + prev + " to " + maxtree[index]);
            }
        }
    }
}