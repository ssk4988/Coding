import java.io.*;
import java.util.*;

public class c {
    static long m = 998244353;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());

        long[][] ncr = new long[65][65];
        ncr[0][0] = 1;
        for(int i = 0; i+1 < ncr.length; i++){
            for(int j = 0; j <= i; j++){
                ncr[i+1][j] = mod(ncr[i+1][j] + ncr[i][j]);
                ncr[i+1][j+1] = mod(ncr[i+1][j+1] + ncr[i][j]);
            }
        }
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            if(n == 2){
                b.append("1 0 1\n");
                continue;
            }
            long d = 1;
            long total = ncr[n][n/2];
            long a = ncr[n-1][n/2-1];
            int num = n-4;
            int denom = n/2 - 3;
            while(num - 1 > 0){
                a = mod(a + ncr[num][denom]);
                a = mod(a + ncr[num-1][denom]);
                num -= 4;
                denom -= 2;
            }
            long boris = mod(total - 1 - a);
            if(boris <= 0){
                boris = (boris + m) % m;
                boris = (boris + m) % m;
            }
            b.append(a + " " + boris + " " + d + "\n");
        }
        System.out.print(b);
        in.close();
    }
    public static long mod(long k){
        return k % m;
    }
}