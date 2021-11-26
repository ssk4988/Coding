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
        composite[1] = composite[0] = true;
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
            String f = tokenizer.nextToken();
            String s = tokenizer.nextToken();
            int mult10 = Math.max(f.split("\\.").length == 1 ? 0 : f.split("\\.")[1].length(),
                    s.split("\\.").length == 1 ? 0 : s.split("\\.")[1].length());
            // System.out.println(mult10);
            if (s.contains(".")) {
                s = s.replaceFirst("\\.", "");
            } else {
                for (int j = 0; j < mult10; j++) {
                    s += "0";
                }
            }
            if (f.contains(".")) {
                f = f.replaceFirst("\\.", "");
            } else {
                for (int j = 0; j < mult10; j++) {
                    f += "0";
                }
            }
            // System.out.println(f + " " + s);
            int first = Integer.parseInt(f);
            int second = Integer.parseInt(s);
            int gcd = gcd(first, second);
            int f2 = first / gcd;
            int s2 = second / gcd;
            if(f2 == s2){
                System.out.println("2 2");
            }
            else if(composite[f2] || composite[s2]){
                System.out.println("impossible");
            }
            else{
                System.out.println(f2 + " " + s2);
            }
            // System.out.println(first + " " + second);
            //solve(primes, composite, first, second);
        }

        in.close();
        out.close();
    }
    public static int gcd(int first, int second){
        if(first < second){
            int tmp = first;
            first = second;
            second = tmp;
        }
        if(second == 0) return first;
        return gcd(second, first % second);
    }
}