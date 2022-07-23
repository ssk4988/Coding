import java.io.*;
import java.util.*;

public class p006v2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int l = Integer.parseInt(tokenizer.nextToken());
        String[] arr = new String[n];
        for (int i = 0; i < n; i++) {
            arr[i] = in.readLine();
        }
        int[][] next = new int[n - 1][l];
        for (int i = 0; i < next.length; i++) {
            int j = 0;
            int prev = 0;
            while (j < l) {
                prev = j;
                while (prev + 1 < l && arr[i].charAt(prev) == arr[i + 1].charAt(prev))
                    prev++;
                while (j <= prev)
                    next[i][j++] = arr[i].charAt(prev) < arr[i + 1].charAt(prev) ? prev : 5000000;
            }
        }
        int bestL = l;
        int bestLeft = 0;
        int bestRight = l - 1;
        for (int j = 0; j < l; j++) {
            int maxindex = j;
            for (int i = 0; i < next.length; i++) {
                maxindex = Math.max(maxindex, next[i][j]);
            }
            if (maxindex - j + 1 < bestL) {
                bestL = maxindex - j + 1;
                bestLeft = j;
                bestRight = maxindex;
            }
        }
        System.out.println((bestLeft + 1) + " " + (bestRight + 1));

        in.close();
    }

}