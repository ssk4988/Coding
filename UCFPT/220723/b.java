import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        long a = Long.parseLong(tokenizer.nextToken());
        long b= Long.parseLong(tokenizer.nextToken());
        long p = Integer.parseInt(tokenizer.nextToken());
        long q = Integer.parseInt(tokenizer.nextToken());
        TreeSet<Long> pows = new TreeSet<>();
        long cur = 1;
        while(cur <= (Long.MAX_VALUE / p)){
            cur *= p;
            pows.add(cur);
            long cur1 = cur;
            while(cur1 <= (Long.MAX_VALUE / (p * q))){
                cur1 *=p;
                cur1 *= q;
                pows.add(cur1);
            }
        }
        long cnt = 0;
        for(long k : pows){
            long[] maxmult = new long[]{(a - 1) / k, b / k};
            for(int i = 0; i < maxmult.length; i++){
                maxmult[i] = maxmult[i] - maxmult[i] / p - maxmult[i] / q + maxmult[i] / (p * q);
            }
            cnt += maxmult[1] - maxmult[0];
        }
        System.out.println(cnt);

        in.close();
    }
}