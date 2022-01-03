/*
ID: ssk49881
LANG: JAVA
TASK: convention
*/

import java.io.*;
import java.util.*;

public class convention {
    public static boolean test = false;

    public static void main(String[] args) throws Exception {

        BufferedReader in = test ? new BufferedReader(new InputStreamReader(System.in))
                : new BufferedReader(new FileReader("convention.in"));
        PrintWriter out = test ? new PrintWriter(System.out)
                : new PrintWriter(new BufferedWriter(new FileWriter("convention.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        int[] times = new int[n];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            times[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(times);
        int low = 0;
        int high = Integer.MAX_VALUE;
        int mid;
        while (low < high) {
            mid = low + (high - low) / 2;
            boolean works = test(mid, m, c, times);
            if (works) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        out.println(low);
        in.close();
        out.close();
    }

    public static boolean test(int val, int m, int c, int[] times) {
        int used = 0;
        int startindex = 0;
        int currindex = 0;
        while (startindex < times.length) {
            currindex = startindex;
            while ((currindex + 1) - startindex + 1 <= c && currindex + 1 < times.length
                    && times[currindex + 1] - times[startindex] <= val) {
                currindex++;
            }
            used++;
            startindex = currindex + 1;
        }
        if (test) {
            System.out.println(val + " time and used buses " + used);
        }

        return used <= m;
    }
}