import java.io.*;
import java.util.*;

public class josephus2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken()) + 1;
        int[] tree = new int[n + 1];
        StringBuilder b = new StringBuilder();
        for (int i = 1; i <= n; i++) {
            update(tree, i, 1);
        }
        int pointer = 0;
        for (int i = n; i > 0; i--) {
            int k1 = k % i;
            if(k1 == 0) k1 = i;
            int low = 0;
            int high = pointer == 0 ? n : n - 1;
            int right = sum(tree, n) - sum(tree, pointer);
            int left = sum(tree, pointer);
            while (low < high) {
                int mid = low + (high - low) / 2;
                int ind = (pointer - 1 + mid) % n + 1;
                int val = ind < pointer ? right + sum(tree, ind) : sum(tree, ind) - left;
                if (val >= k1) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            pointer = (pointer - 1 + low) % n + 1;
            b.append(pointer);
            b.append(i > 1 ? " " : "\n");
            update(tree, pointer, -1);
        }
        System.out.print(b);
        in.close();
    }

    public static void update(int[] tree, int index, int change) {
        while (index < tree.length) {
            tree[index] += change;
            index += index & -index;
        }
    }

    public static int sum(int[] tree, int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
}