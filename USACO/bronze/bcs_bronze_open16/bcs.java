/*
ID: ssk49881
LANG: JAVA
TASK: bcs
*/

import java.io.*;
import java.util.*;

public class bcs {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("bcs.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("bcs.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int dim = Integer.parseInt(tokenizer.nextToken());
        int numPieces = Integer.parseInt(tokenizer.nextToken());
        boolean[][] original = new boolean[dim][dim];
        for (int i = 0; i < dim; i++) {
            String line = in.readLine();
            for (int j = 0; j < dim; j++) {
                if (line.charAt(j) == '#')
                    original[i][j] = true;
            }
        }
        boolean[][][] pieces = new boolean[numPieces][dim][dim];
        int[][][] piecedims = new int[numPieces][2][2];
        for (int[][] d : piecedims) {
            d[0][0] = Integer.MAX_VALUE;
            d[0][1] = Integer.MIN_VALUE;
            d[1][0] = Integer.MAX_VALUE;
            d[1][1] = Integer.MIN_VALUE;
        }
        for (int k = 0; k < numPieces; k++) {
            for (int i = 0; i < dim; i++) {
                String line = in.readLine();
                for (int j = 0; j < dim; j++) {
                    if (line.charAt(j) == '#') {
                        pieces[k][i][j] = true;
                        if (i < piecedims[k][0][0])
                            piecedims[k][0][0] = i;
                        if (i > piecedims[k][0][1])
                            piecedims[k][0][1] = i;
                        if (j < piecedims[k][1][0])
                            piecedims[k][1][0] = j;
                        if (j > piecedims[k][1][1])
                            piecedims[k][1][1] = j;

                    }
                }
            }
        }
        outer: for (int i = 0; i < numPieces; i++) {
            for (int j = 0; j < i; j++) {
                for (int k = -piecedims[i][0][0]; k <= dim - 1 - piecedims[i][0][1]; k++) {
                    for (int m = -piecedims[i][1][0]; m <= dim - 1 - piecedims[i][1][1]; m++) {
                        for (int n = -piecedims[j][0][0]; n <= dim - 1 - piecedims[j][0][1]; n++) {
                            for (int o = -piecedims[j][1][0]; o <= dim - 1 - piecedims[j][1][1]; o++) {
                                boolean[][] newfig = new boolean[dim][dim];
                                for (int p = piecedims[i][0][0]; p <= piecedims[i][0][1]; p++) {
                                    for (int q = piecedims[i][1][0]; q <= piecedims[i][1][1]; q++) {
                                        if (pieces[i][p][q])
                                            newfig[p + k][q + m] = !newfig[p + k][q + m];
                                    }
                                }
                                for (int p = piecedims[j][0][0]; p <= piecedims[j][0][1]; p++) {
                                    for (int q = piecedims[j][1][0]; q <= piecedims[j][1][1]; q++) {
                                        if (pieces[j][p][q])
                                            newfig[p + n][q + o] = !newfig[p + n][q + o];
                                    }
                                }
                                boolean matches = true;
                                for (int x = 0; x < dim; x++) {
                                    for (int y = 0; y < dim; y++) {
                                        if (newfig[x][y] != original[x][y])
                                            matches = false;
                                    }
                                }
                                if (matches) {
                                    out.println((j + 1) + " " + (i + 1));
                                    break outer;
                                }
                            }
                        }
                    }
                }
            }
        }
        in.close();
        out.close();
    }
}