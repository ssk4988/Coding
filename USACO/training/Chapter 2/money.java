/*
ID: ssk49881
LANG: JAVA
TASK: money
*/

import java.io.*;
import java.util.*;

public class money {
    public static ArrayList<Integer> values = new ArrayList<>();
    public static long[][] combos;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("money.in"));
        PrintWriter out = new PrintWriter(new File("money.out"));
        String phrase = in.nextLine();
        int numCoins = Integer.parseInt(phrase.split(" ")[0]);
        int amount = Integer.parseInt(phrase.split(" ")[1]);
        while (in.hasNextLine()) {
            phrase = in.nextLine();
            for (int i = 0; i < phrase.split(" ").length; i++) {
                int newInt = Integer.parseInt(phrase.split(" ")[i]);
                if (newInt > 0) {
                    values.add(newInt);
                    System.out.println(newInt);
                }
            }
        }
        combos = new long[10005][numCoins];
        Collections.sort(values);
        for (long[] arr : combos) {
            Arrays.fill(arr, -1);
        }
        for (int i = 0; i < numCoins; i++) {
            combos[0][i] = 1;
        }
        out.println(combos(amount, values.size() - 1));

        in.close();
        out.close();
    }

    public static long combos(int amount, int maxCoinIndex) {
        if (combos[amount][maxCoinIndex] != -1) {
            return combos[amount][maxCoinIndex];
        }
        if (values.get(0) > amount) {
            combos[amount][maxCoinIndex] = 0;
            return combos[amount][maxCoinIndex];
        }
        long sum = 0;
        //System.out.println(amount + " " + maxCoinIndex);
        for (int i = 0; i <= maxCoinIndex; i++) {
            if (values.get(i) > amount) {
                break;
            }
            if (combos[amount - values.get(i)][i] == -1 && i == 0 && (amount - values.get(i)) % values.get(i) == 0) {
                combos[amount - values.get(i)][0] = 1;
            } else if (combos[amount - values.get(i)][i] == -1) {
                combos(amount - values.get(i), i);
            }
            sum += combos[amount - values.get(i)][i];
        }
        combos[amount][maxCoinIndex] = sum;
        //System.out.println(amount + " " + maxCoinIndex + " " + sum);
        return combos[amount][maxCoinIndex];
    }

}