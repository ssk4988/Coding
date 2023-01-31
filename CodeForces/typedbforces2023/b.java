import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        boolean[] composite = new boolean[10000];
        ArrayList<Integer> primes = new ArrayList<>();
        composite[0] = composite[1] = true;
        for(int i = 2; i < composite.length; i++){
            if(!composite[i]) {
                primes.add(i);
                for(int j = i * i; j < composite.length; j += i){
                    composite[j] = true;
                }
            }
        }
        for (int cn = 0; cn < nc; cn++) {
            int n = Integer.parseInt(in.readLine());
            long n1 = n;
            ArrayList<Integer> f = new ArrayList<>();
            ArrayList<Integer> c = new ArrayList<>();
            if (n % 2 == 0) {
                f.add(2);
                c.add(0);
                while (n % 2 == 0) {
                    n /= 2;
                    c.set(c.size() - 1, c.get(c.size() - 1) + 1);
                }
            }
            for (int i = 0; i < primes.size(); i++) {
                int p = primes.get(i);
                if (n % p == 0) {
                    f.add(p);
                    c.add(0);
                    while (n % p == 0) {
                        n /= p;
                        c.set(c.size() - 1, c.get(c.size() - 1) + 1);
                    }
                }
            }
            if(n > 1){
                f.add(n);
                c.add(1);
            }
            ArrayList<Long> a = new ArrayList<>();
            ArrayList<Integer> p = new ArrayList<>();
            while(true){
                ArrayList<Integer> v = new ArrayList<>();
                v.add(1);
                for(int pow = 1; pow < 35; pow++){
                    int k = 1;
                    for(int i = 0; i < f.size(); i++){
                        if(c.get(i) >= pow){
                            k *= f.get(i);
                        }
                    }
                    if(k == 1) break;
                    v.add(k);
                }
                int maxdex = 0;
                for(int i = 0; i < v.size(); i++){
                    if(v.get(i) > v.get(maxdex)){
                        maxdex = i;
                    }
                }
                if(v.get(maxdex) == 1 || maxdex <= 0) break;
                long k = 1;
                maxdex = 1;
                for(int i = 0; i < f.size(); i++){
                    if(c.get(i) >= maxdex){
                        c.set(i, c.get(i) - maxdex);
                        k *= f.get(i);
                    }
                }
                a.add(k);
                p.add(maxdex);
            }
            long sum = 0;
            for(int i = 0; i < a.size(); i++){
                sum += a.get(i) * p.get(i);
            }
            System.out.println(sum);
        }
        in.close();
    }
}
