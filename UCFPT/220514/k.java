import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int[] nk = new int[k];
        int[] mk = new int[k];
        int[] pk = new int[k];
        TreeSet<Integer> nset = new TreeSet<>();
        TreeSet<Integer> mset = new TreeSet<>();
        for (int i = 0; i < k; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            nk[i] = Integer.parseInt(tokenizer.nextToken());
            mk[i] = Integer.parseInt(tokenizer.nextToken());
            pk[i] = Integer.parseInt(tokenizer.nextToken());
            nset.add(nk[i]);
            mset.add(mk[i]);
        }
        Map<Integer, Integer> nmap = new HashMap<>();
        int ncnt = 0;
        for (int i : nset) {
            nmap.put(i, ncnt);
            ncnt++;
        }
        Map<Integer, Integer> mmap = new HashMap<>();
        int mcnt = 0;
        for (int i : mset) {
            mmap.put(i, mcnt);
            mcnt++;
        }
        int[][] dp = new int[ncnt+6][mcnt+6];
        for (int i = 0; i < k; i++) {
            nk[i] = nmap.get(nk[i]);
            mk[i] = mmap.get(mk[i]);
            dp[nk[i]][mk[i]] += pk[i];
        }
        for (int i = 0; i < dp.length; i++) {
            for (int j = 0; j < dp[i].length; j++) {
                dp[i][j] += Math.max((i > 0 ? dp[i - 1][j] : 0), (j > 0 ? dp[i][j - 1] : 0));
            }
        }
        System.out.println(dp[dp.length - 1][dp[0].length - 1]);
        in.close();
    }
}