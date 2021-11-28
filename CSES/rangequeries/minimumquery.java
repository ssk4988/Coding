/*
ID: ssk49881
LANG: JAVA
TASK: minimumquery
*/

import java.io.*;
import java.util.*;

public class minimumquery {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        int[][] prefix = new int[size][];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < size; i++) {
            prefix[i] = new int[size - i];
            prefix[i][0] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 2; i <= size; i *= 2) {
            for (int j = 0; j + i - 1 < size; j++) {
                prefix[j][i - 1] = Math.min(prefix[j][i / 2 - 1], prefix[j + i / 2][i - i / 2 - 1]);
            }
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int range = second - first + 1;
            int p2 = (int) (Math.log(range) / Math.log(2));
            int smaller2 = (int) Math.pow(2, p2);
            b.append(Math.min(prefix[first][smaller2 - 1], prefix[second - smaller2 + 1][smaller2 - 1]) + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}