import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int[] ns = new int[n];
        int[] ms = new int[m];
        Set<Integer> ms2 = new HashSet<>();
        boolean[] fine = new boolean[300007 + 1];
        int[] right = new int[300007 + 1];
        Arrays.fill(fine, true);
        for (int i = 0; i < n; i++) {
            ns[i] = Integer.parseInt(in.readLine());
        }
        for (int i = 0; i < m; i++) {
            ms[i] = Integer.parseInt(in.readLine());
            ms2.add(ms[i]);
            fine[ms[i]] = false;
        }
        for (int i : ms2) {
            for (int j = i; j < fine.length; j += i) {
                fine[j] = false;
            }
        }
        int r = 300007;
        for (int i = fine.length - 1; i >= 0; i--) {
            if (fine[i])
                r = i;
            right[i] = r;
        }
        long answer = 0;
        for (int i = 0; i < ns.length; i++) {
            answer += right[ns[i]] - ns[i];
        }
        System.out.println(answer);

        in.close();
        out.close();
    }
}