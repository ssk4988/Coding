/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        outer: for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numStudents = Integer.parseInt(tokenizer.nextToken());
            long balance = Long.parseLong(tokenizer.nextToken());
            long[] values = new long[numStudents];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < numStudents; i++) {
                values[i] = Integer.parseInt(tokenizer.nextToken());
            }
            long currBalance = balance;
            int length = 0;
            int maxLength = 0;
            int start = -1;
            for (int i = 0; i < numStudents; i++) {
                while (length > 0 && currBalance + values[i] < 0) {
                    currBalance -= values[i - length];
                    length--;
                }
                if (currBalance + values[i] >= 0) {
                    length++;
                    currBalance += values[i];
                }
                if (length > maxLength) {
                    maxLength = length;
                    start = i - length + 1;
                }
            }
            if (start == -1) {
                System.out.println(start);
            } else {
                System.out.println((start + 1) + " " + (start + maxLength - 1 + 1));
            }
        }

        in.close();
        out.close();
    }
}