/*
ID: ssk49881
LANG: JAVA
TASK: socdist
*/

import java.io.*;
import java.util.*;

public class socdist {
    public static int numCows;
    public static int numRange;
    public static long[] low;
    public static long[] high;
    public static Tuple[] list;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("socdist.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("socdist.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());

        numCows = Integer.parseInt(tokenizer.nextToken());
        numRange = Integer.parseInt(tokenizer.nextToken());
        low = new long[numRange];
        high = new long[numRange];
        list = new Tuple[numRange];
        long maxdist = 0;
        for (int i = 0; i < numRange; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            low[i] = Integer.parseInt(tokenizer.nextToken());
            high[i] = Integer.parseInt(tokenizer.nextToken());
            list[i] = new Tuple(low[i], high[i]);
            if (high[i] - low[i] > maxdist) {
                maxdist = high[i] - low[i];
            }
        }
        Arrays.sort(list);
        long l = 0;
        long r = maxdist;
        while (l < r) {
            long mid = (l + r + 1) / 2;
            // System.out.println(l + " " + mid + " " + r);
            if (test(mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        out.println(l);

        in.close();
        out.close();
    }

    public static boolean test(long d) {
        long cows = 0;
        long startIndex = list[0].first;
        for (int i = 0; i < numRange; i++) {
            long low = list[i].first;
            long high = list[i].second;
            startIndex = Math.max(low, startIndex);
            while (startIndex >= low && startIndex <= high) {
                cows++;
                startIndex += d;
            }
        }
        return cows >= numCows;
    }

    public static class Tuple implements Comparable<Tuple> {
        long first;
        long second;

        public Tuple(long first, long second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int compareTo(socdist.Tuple o) {
            if (this.first < o.first)
                return -1;
            if (this.first == o.first)
                return 0;
            return 1;
        }
    }
}