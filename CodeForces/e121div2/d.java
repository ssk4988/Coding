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
            for (int i = 0; i + 1 < prefix.length; i++) {
                prefix[i + 1] += prefix[i];
            }
            int c = Integer.MAX_VALUE;
            for (int i = 0; i <= prefix.length; i++) {
                int cost = 0;
                int left = i == 0 ? 0 : (i == prefix.length ? n : prefix[i - 1]);
                cost += lowest2(left) - left;
                int right = n - left;
                int max2 = lowest2(right);
                int minOther = max2 - right + 1;
                for (int inc = 1; inc < max2; inc <<= 1) {
                    int search = left + inc;
                    int index = Arrays.binarySearch(prefix, search);
                    if (index < 0) {
                        index = -index - 1;
                    }
                    int l1 = index > prefix.length - 1 ? right : prefix[index] - left;
                    int l2 = right - l1;
                    minOther = Math.min(minOther, lowest2(l1) + lowest2(l2) - l1 - l2);
                    search = n - inc;
                    index = Arrays.binarySearch(prefix, search);
                    if (index < 0) {
                        index = -index - 1;
                        if (index < prefix.length) {
                            index++;
                        }
                    }
                    l1 = index > prefix.length - 1 ? right : prefix[index] - left;
                    l2 = right - l1;
                    minOther = Math.min(minOther, lowest2(l1) + lowest2(l2) - l1 - l2);
                }
                cost += minOther;
                c = Math.min(c, cost);
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