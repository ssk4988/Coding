import java.io.*;
import java.util.*;

public class prob1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] arr = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int[] next = new int[n];
        int[] last = new int[n + 1];
        Arrays.fill(last, n);
        for (int i = n - 1; i >= 0; i--) {
            next[i] = last[arr[i]];
            last[arr[i]] = i;
        }
        int[] prev = new int[n];
        Arrays.fill(last, -1);
        for (int i = 0; i < n; i++) {
            prev[i] = last[arr[i]];
            last[arr[i]] = i;
        }
        TreeSet<Integer>[] suf = new TreeSet[n + 1];
        for (int i = 0; i < suf.length; i++) {// indexes of cows that have prev < k for suf[k]
            suf[i] = new TreeSet<>();
        }
        int negone = 0;
        for (int i = 0; i < n; i++) {
            suf[prev[i] + 1].add(i);
        }
        long[] bit = new long[n + 1];
        long answer = 0;
        for (int i = 0; i < n; i++) {
            for (int k : suf[i]) {
                update(bit, k, 1);
            }
            answer += sum(bit, next[i] - 1) - sum(bit, i);
        }
        System.out.println(answer);

        in.close();
    }

    public static void update(long[] bit, int index, int val) {
        index++;
        while (index < bit.length) {
            bit[index] += val;
            index += index & -index;
        }
    }

    public static long sum(long[] bit, int index) {
        long sum = 0;
        index++;
        while (index > 0) {
            sum += bit[index];
            index -= index & -index;
        }
        return sum;
    }
}