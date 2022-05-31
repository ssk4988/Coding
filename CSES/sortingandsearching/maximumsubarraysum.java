import java.io.*;
import java.util.*;

public class maximumsubarraysum {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        long[] arr = new long[n];
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        for(int i = 0; i < n ;i++){
            arr[i] = Integer.parseInt(tokenizer.nextToken());
        }
        long pref = 0;
        long maxSum = Long.MIN_VALUE;
        for(int i = 0; i < n; i++){
            pref = Math.max(pref, 0);
            pref += arr[i];
            maxSum = Math.max(maxSum, pref);
        }
        System.out.println(maxSum);
        in.close();
    }
}