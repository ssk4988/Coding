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
        int[][] coats = new int[200][200];
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
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++) {
                if (coats[i][j] == k) {
                    area++;
                }
                if (j + 1 < 200) {
                    coats[i][j + 1] += coats[i][j];
                }
            }
        }
        int[][] newcoats = new int[200][200];
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++) {
                if(coats[i][j] == k){
                    newcoats[i][j] = -1;
                }
                if(coats[i][j] == k - 1){
                    newcoats[i][j] = 1;
                }
            }
        }
        int[][] sums = new int[200][200];
        sums[0][0] = newcoats[0][0];
        for(int i = 0; i < 200; i++){
            for(int j = 0; j < 200; j++){
                sums[i][j] = newcoats[i][j];
                if(i > 0){
                    sums[i][j] += sums[i - 1][j];
                }
                if(j > 0){
                    sums[i][j] += sums[i][j - 1];
                }
                if(i > 0 && j > 0){
                    sums[i][j] -= sums[i - 1][j - 1];
                }
            }
        }
        int addarea = 0;


        in.close();
        out.close();
    }
}