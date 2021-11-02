/*
ID: ssk49881
LANG: JAVA
TASK: gift1
*/

import java.io.*;
import java.util.*;

public class gift1 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("gift1.in"));
        PrintWriter out = new PrintWriter(new File("gift1.out"));
        int np = Integer.parseInt(in.nextLine());
        String[] friends = new String[np];
        int[] money = new int[np];
        int[] balance = new int[np];
        for (int i = 0; i < np; i++) {
            friends[i] = in.nextLine();
            balance[i] = 0;
        }
        for (int i = 0; i < np; i++) {
            String name = in.nextLine();
            int index = Arrays.asList(friends).indexOf(name);
            String moneydonors = in.nextLine();
            money[index] = Integer.parseInt(moneydonors.split(" ")[0]);
            int numdonors = Integer.parseInt(moneydonors.split(" ")[1]);
            String[] donors = new String[numdonors];
            for (int j = 0; j < numdonors; j++) {
                donors[j] = in.nextLine();
            }
            for (int k = 0; k < np; k++) {
                if (Arrays.asList(donors).contains(friends[k])) {
                    balance[k] += money[index] / numdonors;
                    balance[index] -= money[index] / numdonors;
                }
            }
        }
        for (int i = 0; i < np; i++) {
            out.println(friends[i] + " " + Integer.toString(balance[i]));
        }
        in.close();
        out.close();
    }
}