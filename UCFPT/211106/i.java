/*
ID: ssk49881
LANG: JAVA
TASK: i
*/

import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int rows = Integer.parseInt(tokenizer.nextToken());
        int val = Integer.parseInt(tokenizer.nextToken());
        int minval = 1;
        for (int i = 1; i < rows; i++) {
            minval *= 2;
        }
        if (val < minval) {
            System.out.println("impossible");
        } else {
            int diff = val - minval;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j <= i; j++) {
                    if (j == 0) {
                        System.out.print(diff + minval);
                    } else {
                        System.out.print(minval);
                    }
                    if (j < i) {
                        System.out.print(" ");
                    }

                }
                minval /= 2;
                System.out.println();
            }
        }

        in.close();
        out.close();
    }
}