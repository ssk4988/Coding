/*
ID: ssk49881
LANG: JAVA
TASK: milk
*/

import java.io.*;
import java.util.*;

public class milk {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("milk.in"));
        PrintWriter out = new PrintWriter(new File("milk.out"));
        String phrase = in.nextLine();
        int n = Integer.parseInt(phrase.split(" ")[0]);
        int m = Integer.parseInt(phrase.split(" ")[1]);
        int costCents = 0;
        int currentStock = 0;
        ArrayList<farmer> farmers = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            phrase = in.nextLine();
            farmers.add(new farmer(phrase));
        }
        Collections.sort(farmers);
        for (int i = 0; currentStock < n; i++) {
            farmer newFarmer = farmers.get(i);
            costCents += newFarmer.rate * Math.min(newFarmer.stock, n - currentStock);
            currentStock += Math.min(newFarmer.stock, n - currentStock);
        }
        out.println(costCents);

        in.close();
        out.close();
    }
}

class farmer implements Comparable<farmer> {
    public int rate;
    public int stock;

    public farmer(String input) {
        this.rate = Integer.parseInt(input.split(" ")[0]);
        this.stock = Integer.parseInt(input.split(" ")[1]);
    }

    @Override
    public int compareTo(farmer o) {
        return this.rate - o.rate;
    }
}