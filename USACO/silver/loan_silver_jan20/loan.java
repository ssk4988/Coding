/*
ID: ssk49881
LANG: JAVA
TASK: loan
*/

import java.io.*;
import java.util.*;

public class loan {
    public static long numLoan;
    public static long numDays;
    public static long minPayment;
    public static long start_time;

    public static void main(String[] args) throws Exception {
        start_time = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("loan.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("loan.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numLoan = Long.parseLong(tokenizer.nextToken());
        numDays = Long.parseLong(tokenizer.nextToken());
        minPayment = Long.parseLong(tokenizer.nextToken());
        long upper = 1;
        boolean condition = true;
        while (condition) {
            condition = valid(numLoan, numDays, minPayment, upper);
            upper *= 2;
        }
        long lower = 1;
        long x = (lower + upper) / 2;
        condition = true;
        while (upper - lower > 1) {
            x = (lower + upper) / 2;
            condition = valid(numLoan, numDays, minPayment, x);
            if (condition) {
                lower = x;
            } else {
                upper = x;
            }
        }
        out.println(lower);
        in.close();
        out.close();
    }

    public static boolean valid(long n, long k, long m, long x) {
        long g = 0;
        while (k > 0 && g < n) {
            long y = (n - g) / x;
            if (y < m) {
                long leftover = (n - g + m - 1) / m;
                return leftover <= k;
            }
            long maxmatch = n - x * y; //
            long numdays = (maxmatch - g) / y + 1;
            if (numdays > k)
                numdays = k;
            g += y * numdays;
            k -= numdays;
            // System.out.println(n + " " + k + " " + numdays + " " + maxmatch + " " + g + "
            // " + y);
        }
        return g >= n;
    }
}