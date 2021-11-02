/*
ID: ssk49881
LANG: JAVA
TASK: paintbarn
*/

import java.io.*;
import java.util.*;

public class paintbarn {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("paintbarn.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("paintbarn.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numRect = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int[][] coats = new int[1000][1000];
        int area = 0;
        for (int i = 0; i < numRect; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken());
            int b = Integer.parseInt(tokenizer.nextToken());
            int c = Integer.parseInt(tokenizer.nextToken());
            int d = Integer.parseInt(tokenizer.nextToken());
            for (int x = a; x < c; x++) {
                coats[x][b]++;
                coats[x][d]--;
            }
        }
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                if (coats[i][j] == k) {
                    area++;
                }
                if (j + 1 < 1000) {
                    coats[i][j + 1] += coats[i][j];
                }
            }
        }
        out.println(area);

        in.close();
        out.close();
    }
}