/*
ID: ssk49881
LANG: JAVA
TASK: cownomics
*/

import java.io.*;
import java.util.*;

public class cownomics {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("cownomics.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cownomics.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numGenes = Integer.parseInt(tokenizer.nextToken());
        int[][][] data = new int[2][numCows][numGenes];
        for (int h = 0; h < 2; h++) {
            for (int i = 0; i < numCows; i++) {
                String genes = in.readLine();
                for (int j = 0; j < genes.length(); j++) {
                    int val = 0;
                    if (genes.charAt(j) == 'A')
                        val = 0;
                    if (genes.charAt(j) == 'C')
                        val = 1;
                    if (genes.charAt(j) == 'T')
                        val = 2;
                    if (genes.charAt(j) == 'G')
                        val = 3;
                    data[h][i][j] = val;
                }
            }
        }
        int numvalid = 0;
        for (int i = 0; i < numGenes; i++) {
            for (int j = 0; j < i; j++) {
                iter: for (int k = 0; k < j; k++) {
                    int[][][][] times = new int[4][4][4][2];
                    for (int l = 0; l < 2; l++) {
                        for (int m = 0; m < numCows; m++) {
                            times[data[l][m][i]][data[l][m][j]][data[l][m][k]][l]++;
                            if (times[data[l][m][i]][data[l][m][j]][data[l][m][k]][1 - l] > 0)
                                continue iter;
                        }
                    }
                    numvalid++;
                }
            }
        }
        out.println(numvalid);

        in.close();
        out.close();
    }
}