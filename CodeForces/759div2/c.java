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
            ArrayList<Integer> pos = new ArrayList<>();
            ArrayList<Integer> neg = new ArrayList<>();
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
            for (int i = pos.size() - 1; i >= 0; i -= k) {
                sum += (long) 2 * pos.get(i);
            }
            for (int i = neg.size() - 1; i >= 0; i -=k) {
                sum += (long) 2 * neg.get(i);
            }
            long possave = pos.size() > 0 ? pos.get(pos.size() - 1) : 0;
            long negsave = neg.size() > 0 ? neg.get(neg.size() - 1) : 0;
            sum -= Math.max(possave, negsave);
            b.append(sum + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}