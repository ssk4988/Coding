import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int max = 100000;
        boolean[] composite = new boolean[max+1];
        composite[0] = true;
        composite[1] = true;
        ArrayList<Long> primes = new ArrayList<>();
        for(int i = 2; i < composite.length; i++){
            if(!composite[i]){
                primes.add((long)i);
            }
            for(int j = i * 2; j < composite.length; j+= i){
                composite[j] = true;
            }
        }
        long val = 1;
        ArrayList<Long> vals = new ArrayList<>();
        vals.add(2L);
        ArrayList<Long> prevs = new ArrayList<>();
        prevs.add(1L);
        for(int i= 0;i <primes.size(); i++){
            val *= primes.get(i);
            if(val > n) break;
            long top = 0;
            for(int j=0; j < i; j++){
                top += val / primes.get(j);
                for(int k = 0; k < j; k++){
                    top -= val / (primes.get(j) * primes.get(k));
                }
                //System.out.println(primes.get(i) + " " + top + " " + primes.get(j));
            }
            top += vals.get(vals.size() - 1) - prevs.get(prevs.size() - 1);
            int count = 0;
            for(long l = 1; l <= val; l++){
                if(gcd(val, l) > 1) count++;
            }
            System.out.println(top + " " + val + " " + count);
            prevs.add(top);
            vals.add(val);
        }
        //System.out.println(primes);
        

        in.close();
        out.close();
    }
    public static long gcd(long a, long b){
        if(b > a) return gcd(b, a);
        if(b == 0) return a;
        return gcd(b, a%b);
    }
}