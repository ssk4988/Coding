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
            // System.out.println(first + " " + second);
            solve(primes, composite, first, second);
        }

        in.close();
        out.close();
    }

    public static void solve(ArrayList<Integer> primes, boolean[] composite, int first, int second) {
        int f1 = first;
        int s1 = second;
        int div = 1;
        for (int p : primes) {
            while (f1 % p == 0 && s1 % p == 0) {
                f1 /= p;
                s1 /= p;
                div *= p;
            }
        }
        if (first == second) {
            System.out.println("2 2");
            return;
        }
        if (!composite[(int) f1] && !composite[(int) s1] && f1 != s1) {
            System.out.println(f1 + " " + s1);
        } else {
            System.out.println("impossible");
            return;
        }
    }
}