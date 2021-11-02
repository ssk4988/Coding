/*
ID: ssk49881
LANG: JAVA
TASK: camelot
*/

import java.io.*;
import java.util.*;

public class camelot {
    public static int maxDistanceKnight = 10400; // max distance for one knight
    public static int maxRows = 40;
    public static int maxColumns = 26;
    public static int[][] cost = new int[maxColumns][maxRows]; // cost of getting knights to this location
    public static int[][] kingcost = new int[maxColumns][maxRows]; // cost of getting knight to collect king
    public static int[][] kdist = new int[maxColumns][maxRows]; // cost of getting king to this square
    public static int[][][] dist = new int[maxColumns][maxRows][2]; // cost of getting current knight to square 0 = no
                                                                    // king 1 = with king
    public static int nrow, ncol;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("camelot.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("camelot.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int pr, pc;
        nrow = Integer.parseInt(tokenizer.nextToken());
        ncol = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        pc = tokenizer.nextToken().toCharArray()[0] - 'A';
        pr = Integer.parseInt(tokenizer.nextToken()) - 1;
        ArrayList<Integer> knightCols = new ArrayList<>();
        ArrayList<Integer> knightRows = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            tokenizer = new StringTokenizer(line);
            while (tokenizer.hasMoreTokens()) {
                knightCols.add(tokenizer.nextToken().toCharArray()[0] - 'A');
                knightRows.add(Integer.parseInt(tokenizer.nextToken()) - 1);
            }
        }
        for (int i = 0; i < nrow; i++) {
            for (int j = 0; j < ncol; j++) {
                kingcost[j][i] = kdist[j][i] = Math.max(Math.abs(pc - j), Math.abs(pr - i));
            }
        }
        for (int x = 0; x < knightCols.size(); x++) {
            pc = knightCols.get(x);
            pr = knightRows.get(x);
            calc_dist(pc, pr);
            for(int i = 0; i < ncol; i++){
                for(int j = 0; j < nrow; j++){
                    cost[i][j] += dist[i][j][0];
                    if(dist[i][j][1] - dist[i][j][0] < kingcost[i][j]){
                        kingcost[i][j] = dist[i][j][1] - dist[i][j][0];
                    }
                }
            }
        }
        int minCost = cost[0][0] + kingcost[0][0];
        for(int i = 0; i < ncol; i++){
            for(int j = 0; j < nrow; j++){
                if(cost[i][j] + kingcost[i][j] < minCost){
                    minCost = cost[i][j] + kingcost[i][j];
                }
            }
        }
        out.println(minCost);

        in.close();
        out.close();
    }

    public static void calc_dist(int col, int row) {
        int max;
        int f;
        for(int i = 0; i < ncol; i++){
            for(int j = 0; j < nrow; j++){
                dist[i][j][0] = dist[i][j][1] = maxDistanceKnight;
            }
        }
        dist[col][row][0] = 0;
        max = dist[col][row][1] = kdist[col][row];
        for(int d = 0; d <= max; d++){
            for(int i = 0; i < ncol; i++){
                for(int j = 0; j < nrow; j++){
                    if(dist[i][j][0] == d){
                        f = do_step(i, j, 0);
                        if(d + f > max){
                            max = d + f;
                        }
                    }
                    if(dist[i][j][1] == d){
                        f = do_step(i, j, 1);
                        if(d + f > max){
                            max = d + f;
                        }
                    }
                }
            }
        }
    }

    public static int do_step(int x, int y, int kflag) {
        int f = 0; /* maximum distance added */
        int d = dist[x][y][kflag]; /* distance of current move */

        /* go through all possible moves that a knight can make */
        if (y > 0) {
            if (x > 1)
                if (dist[x - 2][y - 1][kflag] > d + 1) {
                    dist[x - 2][y - 1][kflag] = d + 1;
                    f = 1;
                }
            if (x < ncol - 2) {
                if (dist[x + 2][y - 1][kflag] > d + 1) {
                    dist[x + 2][y - 1][kflag] = d + 1;
                    f = 1;
                }
            }
            if (y > 1) {
                if (x > 0)
                    if (dist[x - 1][y - 2][kflag] > d + 1) {
                        dist[x - 1][y - 2][kflag] = d + 1;
                        f = 1;
                    }
                if (x < ncol - 1)
                    if (dist[x + 1][y - 2][kflag] > d + 1) {
                        dist[x + 1][y - 2][kflag] = d + 1;
                        f = 1;
                    }
            }
        }
        if (y < nrow - 1) {
            if (x > 1)
                if (dist[x - 2][y + 1][kflag] > d + 1) {
                    dist[x - 2][y + 1][kflag] = d + 1;
                    f = 1;
                }
            if (x < ncol - 2) {
                if (dist[x + 2][y + 1][kflag] > d + 1) {
                    dist[x + 2][y + 1][kflag] = d + 1;
                    f = 1;
                }
            }
            if (y < nrow - 2) {
                if (x > 0)
                    if (dist[x - 1][y + 2][kflag] > d + 1) {
                        dist[x - 1][y + 2][kflag] = d + 1;
                        f = 1;
                    }
                if (x < ncol - 1)
                    if (dist[x + 1][y + 2][kflag] > d + 1) {
                        dist[x + 1][y + 2][kflag] = d + 1;
                        f = 1;
                    }
            }
        }

        /* also check the 'pick up king here' move */
        if (kflag == 0 && dist[x][y][1] > d + kdist[x][y]) {
            dist[x][y][1] = d + kdist[x][y];
            if (kdist[x][y] > f)
                f = kdist[x][y];
        }
        return f; /* 1 if simple knight move made, 0 if no new move found */
    }
}