import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        ArrayList<Integer> primes = new ArrayList<>();
        boolean[] isPrime = new boolean[100000];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        for(int i = 2; i < isPrime.length; i++){
            if(isPrime[i]) primes.add(i);
            for(int j = i * 2; j < isPrime.length; j += i){
                isPrime[j] = false;
            }
        }
        StringBuilder b= new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            for(int i = 0; i < n; i++){
                b.append(primes.get(i) + (i < n - 1 ? " " : "\n"));
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}