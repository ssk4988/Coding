import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int upper2 = lowest2(n);
            int[] powers = new int[(int)(Math.log(upper2) / Math.log(2))+1];
            powers[0] = 1;
            for(int i = 1; i < powers.length; i++){
                powers[i] = 2 * powers[i-1];
            }
            int[] a = new int[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            Set<Integer> set = new TreeSet<>();
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(tokenizer.nextToken());
                set.add(a[i]);
            }
            Map<Integer, Integer> map = new HashMap<>();
            int k = 0;
            for (int s : set) {
                map.put(s, k);
                k++;
            }
            int[] freq = new int[k];
            int[] prefix = new int[k];
            int[] left = new int[powers.length];
            int[] right = new int[powers.length];
            for (int i = 0; i < n; i++) {
                a[i] = map.get(a[i]);
                freq[a[i]]++;
                prefix[a[i]]++;
            }
            int leftsum = 0;
            int rightsum = 0;
            int l2 = 0;
            int r2 = 0;
            for(int i = 0; i < k; i++){
                leftsum += freq[i];
                rightsum += freq[k - 1 - i];
                while(powers[l2] < leftsum){
                    l2++;
                }
                while(powers[r2] < rightsum){
                    r2++;
                }
                left[l2] = leftsum;
                right[r2] = rightsum;
            }
            for (int i = 0; i + 1 < prefix.length; i++) {
                prefix[i + 1] += prefix[i];
            }
            int c = Integer.MAX_VALUE;
            for(int i = 0; i < left.length; i++){
                for(int j = 0; j < right.length; j++){
                    int mid = n - left[i] - right[j];
                    c = Math.min(c, powers[i] - left[i] + powers[j] - right[j] + lowest2(mid) - mid);
                }
            }
            System.out.println(c);
        }

        in.close();
        out.close();
    }

    public static int lowest2(int val) {
        int next = val;
        int count = -1;
        while (next > 0) {
            count++;
            next >>= 1;
        }
        if (count == -1) {
            return 1;
        }
        if ((1 << count) == val) {
            return val;
        }
        return (1 << (count + 1));
    }
}