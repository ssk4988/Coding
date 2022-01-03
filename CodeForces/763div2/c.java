import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numCases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numCases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            long[] arr = new long[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                arr[i] = Long.parseLong(tokenizer.nextToken());
            }
            long low = 0;
            long high = 1000000000;
            low--;
            while (low < high) {
                long mid = low + (high - low + 1) / 2;
                boolean works = test(arr, mid);
                if (works) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
                //System.out.println(mid + " " + works);
            }
            System.out.println(low);
        }
        in.close();
        out.close();
    }

    public static boolean test(long[] arr, long k) {
        long[] h = new long[arr.length];
        for (int i = 0; i < arr.length; i++) {
            h[i] = arr[i];
        }
        for (int i = h.length - 1; i - 2 >= 0; i--) {
            if (h[i] < k)
                break;
            long d = Math.min((h[i]-k) / 3, arr[i]/3);
            h[i] -= 3 * d;
            h[i - 1] += d;
            h[i-+ 2] += 2 * d;
        }
        for (int i = 0; i < h.length; i++) {
            if (h[i] < k)
                return false;
        }
        //System.out.println(Arrays.toString(h));
        return true;
    }
}