import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out = new StringBuilder();
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            long[] pref = new long[n];
            tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < k; i++){
                pref[n-k + i] = Long.parseLong(tokenizer.nextToken());
            }
            if(k == 1){
                out.append("YES\n");
                continue;
            }
            boolean works = true;
            for(int i = n - 1; i > n - k; i--){
                pref[i] -= pref[i-1];
            }
            for(int i = n - k + 1; i+ 1< n; i++){
                if(pref[i]>pref[i+1]) works = false;
            }

            long cur = pref[n-k];
            if(cur > (n - k + 1) * pref[n-k+1]){
                works = false;
            }
            out.append(works ? "YES\n" : "NO\n");
        }
        System.out.print(out);
        in.close();
    }
}