import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            long k = Long.parseLong(tokenizer.nextToken());
            long[] arr = new long[n];
            tokenizer = new StringTokenizer(in.readLine());
            long sum = 0;
            for (int i = 0; i < n; i++) {
                sum += arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            ruffleSort(arr);
            long answer = Math.max(0, sum - k);
            //System.out.println(casenum + " answer init: " + answer);
            if (sum > k) {
                long sum2 = 0;
                int count = 1;
                long val = sum - k;
                for (int i = arr.length - 1; i > 0; i--) {
                    count++;
                    sum2 += arr[i] - arr[0];
                    answer = Math.min(answer, count - 1 + Math.max(0, (val - sum2 + count - 1) / count));
                }
            }
            b.append(answer + "\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
    static void ruffleSort(long[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            long temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
        Arrays.sort(a);
    }
}