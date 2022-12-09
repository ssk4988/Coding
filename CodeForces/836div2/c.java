import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder out =new StringBuilder();
        cas: for(int cn = 0; cn < nc; cn++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int x = Integer.parseInt(tokenizer.nextToken());
            if(n % x != 0){
                out.append("-1\n");
                continue cas;
            }
            int[] ans = new int[n];
            for(int i = 0; i < n; i++){
                ans[i] = i + 1;
            }
            ans[0] = x;
            ans[x - 1] = 1;
            int cur = x;
            w: while(cur != n){
                for(int i = cur * 2; i <= n; i += cur){
                    if(n % i == 0){
                        int tmp = ans[cur - 1];
                        ans[cur - 1] = ans[i - 1];
                        ans[i - 1] = tmp;
                        cur = i;
                        continue w;
                    }
                }
                out.append("-1\n");
                continue cas;
            }
            
            for(int i = 0; i < n; i++){
                out.append(ans[i] + (i + 1 < n ? " " : "\n"));
            }
            
        }
        System.out.print(out);
        in.close();
    }
}