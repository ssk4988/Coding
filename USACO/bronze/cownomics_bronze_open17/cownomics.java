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
        char[][][] cows = new char[2][numCows][numGenes];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < numCows; j++) {
                String genes = in.readLine();
                for (int k = 0; k < genes.length(); k++) {
                    cows[i][j][k] = genes.charAt(k);
                }
            }
        }
        int indicators = 0;
        for (int i = 0; i < numGenes; i++) {
            boolean aspot = false;
            boolean cspot = false;
            boolean gspot = false;
            boolean tspot = false;
            boolean aplain = false;
            boolean cplain = false;
            boolean gplain = false;
            boolean tplain = false;
            for (int j = 0; j < numCows; j++) {
                if (cows[0][j][i] == 'A') {
                    aspot = true;
                }
                if (cows[0][j][i] == 'C') {
                    cspot = true;
                }
                if (cows[0][j][i] == 'G') {
                    gspot = true;
                }
                if (cows[0][j][i] == 'T') {
                    tspot = true;
                }
                if (cows[1][j][i] == 'A') {
                    aplain = true;
                }
                if (cows[1][j][i] == 'C') {
                    cplain = true;
                }
                if (cows[1][j][i] == 'G') {
                    gplain = true;
                }
                if (cows[1][j][i] == 'T') {
                    tplain = true;
                }
            }
            if ((aspot && aplain) || (cspot && cplain) || (gspot && gplain) || (tspot && tplain)) {

            } else {
                indicators++;
            }
        }
        out.println(indicators);

        in.close();
        out.close();
    }
}