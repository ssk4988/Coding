import java.io.*;
import java.util.*;

public class listremoval {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int size = Integer.parseInt(in.readLine());
        int size2 = size;
        while ((size2 & -size2) != size2)
            size2 += size2 & -size2;
        int[] arr = new int[size];
        int[] tree = new int[2 * size2];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < size; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken());
            update(tree, i, 1, size2);
        }
        tokenizer = new StringTokenizer(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < size; i++) {
            int index = Integer.parseInt(tokenizer.nextToken());
            int low = 0;
            int high = size - 1;
            int mid, curr;
            // System.out.println("Index: " + index);
            do {
                mid = low + (high - low) / 2;
                curr = range(tree, 0, mid, size2);
                // System.out.println("Low: " + low + " mid: " + mid + " High: " + high + "
                // curr: " + curr);
                if (curr < index) {
                    low = Math.min(high, mid + 1);
                } else if (curr > index) {
                    high = Math.max(mid - 1, low);
                } else if (tree[size2 + mid] == 0) {
                    high = Math.max(mid - 1, low);
                } else {
                    low = high = mid;
                    break;
                }
            } while (low <= high);
            // System.out.println(mid);
            b.append(arr[mid] + (i < size - 1 ? " " : "\n"));
            update(tree, mid, 0, size2);
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static void update(int[] tree, int index, int value, int size) {
        index += size;
        tree[index] = value;
        for (index >>= 1; index >= 1; index >>= 1) {
            tree[index] = tree[2 * index] + tree[2 * index + 1];
        }
    }

    public static int range(int[] tree, int i1, int i2, int size) {
        i1 += size;
        i2 += size;
        int sum = 0;
        while (i1 <= i2) {
            if ((i1 & 1) == 1)
                sum += tree[i1++];
            if ((i2 & 1) == 0)
                sum += tree[i2--];
            i1 >>= 1;
            i2 >>= 1;
        }
        return sum;
    }
}