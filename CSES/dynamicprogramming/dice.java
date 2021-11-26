/*
ID: ssk49881
LANG: JAVA
TASK: dice
*/

import java.io.*;
import java.util.*;

public class dice {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int start = Integer.parseInt(in.readLine());
        long[] ways = new long[start + 1];
        ways[0] = 1;
        for (int i = 0; i < ways.length; i++) {
            for (int j = 6; j > 0; j--) {
                if (i - j >= 0) {
                    ways[i] += ways[i - j];
                }
            }
            ways[i] %= 1000000007;
        }
        System.out.println(ways[start]);

        in.close();
    }
}