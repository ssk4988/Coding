/*
ID: ssk49881
LANG: JAVA
TASK: rental
*/

import java.io.*;
import java.util.*;

public class rental {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("6.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new
        // FileWriter("rental.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numStores = Integer.parseInt(tokenizer.nextToken());
        int numFarms = Integer.parseInt(tokenizer.nextToken());
        int[] cows = new int[numCows];
        Store[] stores = new Store[numStores];
        int[] farms = new int[numFarms];
        for (int i = 0; i < numCows; i++) {
            cows[i] = Integer.parseInt(in.readLine());
        }
        for (int i = 0; i < numStores; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int capacity = Integer.parseInt(tokenizer.nextToken());
            int price = Integer.parseInt(tokenizer.nextToken());
            stores[i] = new Store(capacity, price);
        }
        for (int i = 0; i < numFarms; i++) {
            farms[i] = Integer.parseInt(in.readLine());
        }
        Arrays.sort(cows);
        Arrays.sort(stores);
        Arrays.sort(farms);

        long profit = 0;
        int cowIndexLow = 0;
        int cowIndexHigh = numCows - 1;
        int farmIndex = numFarms - 1;
        int storeIndex = 0;
        int count = 0;
        while (cowIndexLow <= cowIndexHigh && farmIndex >= 0 && storeIndex < numStores) {
            long storeProfitMax = 0;
            int ogStoreIndex = storeIndex;
            int cowAmount = cows[cowIndexHigh];
            int storeAmount = stores[storeIndex].capacity;
            while (cowAmount > 0 && farmIndex >= 0 && storeIndex < numStores) {
                int quantityUse = Math.min(cowAmount, storeAmount);
                cowAmount -= quantityUse;
                storeAmount -= quantityUse;
                storeProfitMax += stores[storeIndex].price * quantityUse;
                // System.out.println(storeProfitMax + " " + quantityUse + " " +
                // stores[storeIndex].price);
                if (storeAmount == 0) {
                    storeIndex++;
                    if (storeIndex < numStores) {
                        storeAmount = stores[storeIndex].capacity;
                    }
                }
            }
            long farmProfit = farms[farmIndex];
            if (storeProfitMax > farmProfit) {
                profit += storeProfitMax;
                // System.out.println(profit + " store " + storeProfitMax);
                if(storeIndex < numStores)
                    stores[storeIndex].capacity = storeAmount;
                cowIndexHigh--;
            } else {
                profit += farmProfit;
                // System.out.println(profit + " farm " + farmProfit);
                storeIndex = ogStoreIndex;
                farmIndex--;
                cowIndexLow++;
            }
        }
        System.out.println(profit);

        in.close();
        // out.close();
    }

    public static class Store implements Comparable<Store> {
        int capacity;
        int price;

        public Store(int capacity, int price) {
            this.capacity = capacity;
            this.price = price;
        }

        @Override
        public int compareTo(rental.Store o) {
            return o.price - this.price;
        }
    }
}