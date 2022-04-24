import java.io.*;
import java.util.*;

public class sieve {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            boolean[] composite = new boolean[n + 1];
            ArrayList<Integer> primes = new ArrayList<>();
            ArrayList<Integer> elim = new ArrayList<>();
            for (int i = 2; i < composite.length; i++) {
                if (!composite[i]) {
                    primes.add(i);
                    for (int j = 2 * i; j < composite.length; j += i) {
                        if(!composite[j]){
                            elim.set(j, elim.get(i)+1);
                        }
                    }
                }
            }
        }
        in.close();
        out.close();
    }
}