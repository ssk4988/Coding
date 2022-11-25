import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            String s = in.readLine();
            long ans = 0;
            for(int i = 0; i < n; i++){
                int distinct = 0;
                int[] freq = new int[10];
                int maxfreqf = 0;
                int ub = Math.min(i + 100, n);
                for(int j = i; j < ub; j++){
                    int k = s.charAt(j) - '0';
                    if(freq[k] == 0){
                        distinct++;
                    }
                    freq[k]++;
                    maxfreqf = Math.max(maxfreqf, freq[k]);
                    if(maxfreqf <= distinct) ans++;
                }
            }
            System.out.println(ans);
        }
        in.close();
    }
}