/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int maxNum = 10000000;
        ArrayList<Integer> primes = new ArrayList<>();
        boolean[] composite = new boolean[maxNum + 1];
        for (int i = 2; i <= maxNum; i++) {
            if (composite[i])
                continue;
            primes.add(i);
            for (int j = 2 * i; j < composite.length; j += i) {
                composite[j] = true;
            }
        }
        // System.out.println(primes.size());
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            double f = Double.parseDouble(tokenizer.nextToken());
            double s = Double.parseDouble(tokenizer.nextToken());
            int mult = 1000000;
            long first = Math.round(mult * f);
            long second = Math.round(mult * s);
            double aspect = f / s;
            // System.out.println(first + " " + second);
            long first2 = first;
            long second2 = second;
            int div = 1;
            for (int p : primes) {
                while (first % p == 0 && second % p == 0) {
                    first /= p;
                    second /= p;
                    div *= p;
                }
            }

            pcycle: for(int p : primes){
                int n2 = (int)Math.round(p * aspect);
                int index = Collections.binarySearch(primes, n2);
                if(index < 0){
                    index = -index - 1;
                }
                ArrayList<Integer> candidates = new ArrayList<>();
                candidates.add(index);
                if(index > 0){
                    candidates.add(index - 1);
                }
                if(index < candidates.size() - 1){
                    candidates.add(index + 1);
                }
                
                for(int c : candidates){
                    if(Math.abs(f - s * c / p) < 5e-6){
                        System.out.println(i + " " + c + " " + p + " " + s * c / p + " " + f);
                    }
                }
            }

            if (composite[(int) first] || composite[(int) second]) {
                System.out.println("impossible");
            } else {
                System.out.println(first + " " + second);
            }
        }

        in.close();
        out.close();
    }
}