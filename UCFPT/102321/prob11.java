/*
ID: ssk49881
LANG: JAVA
TASK: prob11
*/

import java.io.*;
import java.util.*;

public class prob11 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int[] place = new int[n];
        int[] reverse = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            place[i] = Integer.parseInt(tokenizer.nextToken());
            reverse[place[i] - 1] = i;
        }
        // System.out.println(Arrays.toString(reverse));
        String[] answer = new String[n];
        Arrays.fill(answer, "1");
        String zstring = "0";

        String ansstr = "";
        for (int i = 0; i < n; i++) {
            answer[i] += (i + 1);
        }
        for (int i = 0; i < n; i++) {
            // place[reverse[i]]
            answer[reverse[i]] += zstring;
            zstring += "0";
        }
        for (int i = 0; i < n; i++) {
            ansstr += answer[i];
            if (i < n - 1) {
                ansstr += " ";
            }
        }
        // System.out.println(Arrays.toString(answer));
        System.out.println(ansstr);
        in.close();
        out.close();
    }
}