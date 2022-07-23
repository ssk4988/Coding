/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int maxNum = 1100000;
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
        long a = Long.parseLong(in.readLine());
        int[] numFactor = new int[primes.size()];
        while (a != 0) {
            long a2 = a * a;
            long acopy = a;
            Map<Integer, Integer> primefactormap = new HashMap<>();
            for (int i = 0; i < primes.size(); i++) {
                while (acopy % primes.get(i) == 0) {
                    if(!primefactormap.containsKey(primes.get(i))){
                        primefactormap.put(primes.get(i), 0);
                    }
                    primefactormap.put(primes.get(i), primefactormap.get(primes.get(i))+1);
                    acopy /= primes.get(i);
                    //System.out.println(num + " " + acopy + " " + primes.get(i));
                }
            }
            ArrayList<Integer> primefactors = new ArrayList<>();
            ArrayList<Integer> values = new ArrayList<>();
            for(int key : primefactormap.keySet()){
                primefactors.add(key);
                values.add(2 * primefactormap.get(key));
            }
            ArrayList<Long> factors = new ArrayList<>();
            getFactors(factors, primefactors, values, 0, 1, 0);
            long answer = 0;
            Collections.sort(factors);
            //System.out.println(num + " " + factors.size());
            for(int i = 0; i < factors.size(); i++){
                long e = factors.get(i);
                long f = a2 / e;
                if(e > f) break;
                if((f - e) % 2 != 0) continue;
                //if((f - e) / 2 <= a) break;
                long b = (f - e) / 2;
                if(b > a) answer++;
            }
            System.out.println(answer);
            a = Long.parseLong(in.readLine());
        }
        // System.out.println(primes.size());

        in.close();
        out.close();
    }

    public static void getFactors(ArrayList<Long> factors, ArrayList<Integer> primefactors, ArrayList<Integer> values, int pindex, long val, int vval) {
        factors.add(val);
        for(int i = pindex; i < primefactors.size(); i++){
            if(i == pindex && vval < values.get(pindex)){
                getFactors(factors, primefactors, values, i, val*primefactors.get(i), vval+1);
            }
            else if (i != pindex){
                getFactors(factors, primefactors, values, i, val*primefactors.get(i), 1);
            }
        }
    }
}