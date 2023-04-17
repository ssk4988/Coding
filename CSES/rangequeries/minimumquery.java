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
        int[][] prefix = new int[20][size];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; (1 << i) <= size; i++) {
            prefix[i] = new int[size + 1 - (1 << i)];
        }
        for(int i = 0; i < size; i++){
            prefix[0][i] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 1; (1 << i) <= size; i++) {
            for (int j = 0; j < prefix[i].length; j++) {
                prefix[i][j] = Math.min(prefix[i - 1][j], prefix[i - 1][j + (1 << (i - 1))]);
            }
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int range = second - first + 1;
            int p;
            for(p = 0; (1 << (p + 1)) <= range; p++);
            b.append(Math.min(prefix[p][first], prefix[p][second + 1 - (1 << p)]) + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }
}
