/*
ID: ssk49881
LANG: JAVA
TASK: shopping
*/

import java.io.*;
import java.util.*;

public class shopping {
    public static Offer[] offers;
    public static int[] prices;
    public static int[] numNeeded;
    public static int numOffers;
    public static int numProductsNeeded;
    public static ArrayList<Integer> codeToIndex;
    public static HashMap<String, Integer> cost = new HashMap<>();

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("shopping.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shopping.out")));
        numOffers = Integer.parseInt(in.readLine());
        offers = new Offer[numOffers];
        String[] offerStrings = new String[numOffers];
        for (int i = 0; i < numOffers; i++) {
            offerStrings[i] = in.readLine();
        }
        codeToIndex = new ArrayList<>();
        prices = new int[5];
        numNeeded = new int[5];
        numProductsNeeded = Integer.parseInt(in.readLine());
        for (int i = 0; i < numProductsNeeded; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int productCode = Integer.parseInt(tokenizer.nextToken());
            int index = codeToIndex.indexOf(productCode);
            if (index == -1) {
                index = codeToIndex.size();
                codeToIndex.add(productCode);
            }
            numNeeded[index] = Integer.parseInt(tokenizer.nextToken());
            prices[index] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 0; i < numOffers; i++) {
            StringTokenizer tokenizer = new StringTokenizer(offerStrings[i]);
            int numDifferentProducts = Integer.parseInt(tokenizer.nextToken());
            int[] numProducts = new int[5];
            for (int j = 0; j < numDifferentProducts; j++) {
                numProducts[codeToIndex.indexOf(Integer.parseInt(tokenizer.nextToken()))] = Integer.parseInt(tokenizer.nextToken());
            }
            int price = Integer.parseInt(tokenizer.nextToken());
            offers[i] = new Offer(numProducts, price);
        }
        int[][][][][] costs = new int[numNeeded[0] + 1][numNeeded[1] + 1][numNeeded[2] + 1][numNeeded[3]
                + 1][numNeeded[4] + 1];
        for (int[][][][] i : costs) {
            for (int[][][] j : i) {
                for (int[][] k : j) {
                    for (int[] l : k) {
                        Arrays.fill(l, 1000000);
                    }
                }
            }
        }
        costs[0][0][0][0][0] = 0;
        if (numNeeded[0] != 0)
            costs[1][0][0][0][0] = prices[0];
        if (numNeeded[1] != 0)
            costs[0][1][0][0][0] = prices[1];
        if (numNeeded[2] != 0)
            costs[0][0][1][0][0] = prices[2];
        if (numNeeded[3] != 0)
            costs[0][0][0][1][0] = prices[3];
        if (numNeeded[4] != 0)
            costs[0][0][0][0][1] = prices[4];
        for (int i = 0; i < costs.length; i++) {
            for (int j = 0; j < costs[i].length; j++) {
                for (int k = 0; k < costs[i][j].length; k++) {
                    for (int l = 0; l < costs[i][j][k].length; l++) {
                        for (int m = 0; m < costs[i][j][k][l].length; m++) {
                            if (i > 0 && costs[i][j][k][l][m] > costs[i - 1][j][k][l][m] + prices[0]) {
                                costs[i][j][k][l][m] = costs[i - 1][j][k][l][m] + prices[0];
                            }
                            if (j > 0 && costs[i][j][k][l][m] > costs[i][j - 1][k][l][m] + prices[1]) {
                                costs[i][j][k][l][m] = costs[i][j - 1][k][l][m] + prices[1];
                            }
                            if (k > 0 && costs[i][j][k][l][m] > costs[i][j][k - 1][l][m] + prices[2]) {
                                costs[i][j][k][l][m] = costs[i][j][k - 1][l][m] + prices[2];
                            }
                            if (l > 0 && costs[i][j][k][l][m] > costs[i][j][k][l - 1][m] + prices[3]) {
                                costs[i][j][k][l][m] = costs[i][j][k][l - 1][m] + prices[3];
                            }
                            if (m > 0 && costs[i][j][k][l][m] > costs[i][j][k][l][m - 1] + prices[4]) {
                                costs[i][j][k][l][m] = costs[i][j][k][l][m - 1] + prices[4];
                            }
                            for (int n = 0; n < offers.length; n++) {
                                if (i >= offers[n].numProducts[0] && j >= offers[n].numProducts[1]
                                        && k >= offers[n].numProducts[2] && l >= offers[n].numProducts[3]
                                        && m >= offers[n].numProducts[4]) {
                                    if (costs[i][j][k][l][m] > offers[n].price
                                            + costs[i - offers[n].numProducts[0]][j - offers[n].numProducts[1]][k
                                                    - offers[n].numProducts[2]][l - offers[n].numProducts[3]][m
                                                            - offers[n].numProducts[4]]) {
                                        costs[i][j][k][l][m] = offers[n].price
                                                + costs[i - offers[n].numProducts[0]][j - offers[n].numProducts[1]][k
                                                        - offers[n].numProducts[2]][l - offers[n].numProducts[3]][m
                                                                - offers[n].numProducts[4]];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        out.println(costs[numNeeded[0]][numNeeded[1]][numNeeded[2]][numNeeded[3]][numNeeded[4]]);
        in.close();
        out.close();
    }

    public static class Offer{
        public int[] numProducts;
        public int price;

        public Offer(int[] numProducts, int price) {
            this.numProducts = numProducts;
            this.price = price;
        }
    }
}