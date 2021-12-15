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
            int k = Integer.parseInt(tokenizer.nextToken());
            long sum = 0;
            int[] arr = new int[n];
            int rem = n % k;
            ArrayList<Integer> pos = new ArrayList<>();
            ArrayList<Integer> neg = new ArrayList<>();
            ArrayList<Integer> pos2 = new ArrayList<>();
            ArrayList<Integer> neg2 = new ArrayList<>();
            ArrayList<Integer> dist = new ArrayList<>();
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                arr[i] = Integer.parseInt(tokenizer.nextToken());
                if (arr[i] >= 0) {
                    pos.add(arr[i]);
                } else {
                    neg.add(-arr[i]);
                }
            }
            Collections.sort(pos);
            Collections.sort(neg);
            for (int i = Math.min(pos.size() - 1, k - 1); i >= 0
                    && i < pos.size(); i = Math.min(pos.size() - 1, i + k)) {
                sum += (long) 2 * pos.get(i);
                pos2.add(i);
                if (i == pos.size() - 1)
                    break;
            }
            for (int i = Math.min(neg.size() - 1, k - 1); i >= 0
                    && i < neg.size(); i = Math.min(neg.size() - 1, i + k)) {
                sum += (long) 2 * neg.get(i);
                neg2.add(i);
                if (i == neg.size() - 1)
                    break;
            }
            long possave = pos2.size() > 0 ? pos.get(pos2.get(pos2.size() - 1)) : 0;
            if (pos2.size() >= 2) {
                possave += (long) 2
                        * ((long) pos.get(pos2.get(pos2.size() - 2)) - pos.get(pos2.get(pos2.size() - 1) - k));
            }
            long negsave = neg2.size() > 0 ? neg.get(neg2.get(neg2.size() - 1)) : 0;
            if (neg2.size() >= 2) {
                negsave += (long) 2
                        * ((long) neg.get(neg2.get(neg2.size() - 2)) - neg.get(neg2.get(neg2.size() - 1) - k));
            }
            sum -= Math.max(possave, negsave);
            b.append(sum + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}