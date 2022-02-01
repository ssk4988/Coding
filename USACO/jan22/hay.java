import java.io.*;
import java.util.*;

public class hay {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] j = new int[n];
        long[] c = new long[n];
        long[] k = new long[n];
        int[] end = new int[n]; // end[i] = first k where j[k] = i
        Arrays.fill(end, -1);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        boolean[] diff = new boolean[n];
        Arrays.fill(diff, true);
        for (int i = 0; i < n; i++) {
            j[i] = Integer.parseInt(tokenizer.nextToken()) - 1;

            if (i == 0) {
                c[0] = 0;
                k[0] = 0;
            } else {
                if (end[i] >= 0) { // k away from first reference (max value)
                    c[i] = c[end[i]];
                    k[i] = k[end[i]] + 1;
                    diff[i] = end[i - 1] >= 0 || j[i] != j[i - 1];
                } else if (j[i - 1] < i) { // out of range of previous (min value)
                    c[i] = c[i - 1] + 1;
                    k[i] = k[i - 1] + 1;
                } else if (end[i - 1] >= 0 || j[i] != j[i - 1]) { // have to be different (min value)
                    c[i] = c[i - 1] + 1;
                    k[i] = k[i - 1];
                } else// if(j[i] == j[i-1]) (min value)
                {
                    c[i] = c[i - 1];
                    k[i] = k[i - 1];
                    diff[i] = false;
                }
            }
            if (end[j[i]] == -1)
                end[j[i]] = i;
        }
        long maxVal = 1000000000000000000L;
        long maxK = maxVal;
        for (int i = 0; i < n; i++) {
            // maxVal >= k[i] * k + c[i]
            if (k[i] == 0)
                continue;
            long currK = (maxVal - c[i]) / k[i];
            maxK = Math.min(maxK, currK);
        }
        long low = 1;
        long high = maxK + 1;
        long[] arr = new long[n];
        while (low < high) {
            long mid = low + (high - low) / 2;
            boolean works = true;
            arr = new long[n];
            for (int i = 1; i < n; i++) {
                arr[i] = mid * k[i] + c[i];
                if (arr[i] < arr[i - 1] // || (arr[i] == arr[i-1] && diff[i])
                ) {
                    works = false;
                    break;
                }

            }
            for (int i = 0; i < n; i++) {
                if (arr[j[i]] > arr[i] + mid || (j[i] + 1 < n && arr[j[i] + 1] <= arr[i] + mid)) {
                    works = false;
                    break;
                }
            }
            if (works) {
                high = low = mid;
                break;
            } else {
                low = mid + 1;
            }
        }
        // System.out.println(Arrays.toString(c));
        // System.out.println(Arrays.toString(k));
        System.out.println(low);
        for (int i = 0; i < n; i++) {
            System.out.println(arr[i]);
        }
        // System.out.println(Arrays.toString(arr));
        in.close();
    }
}