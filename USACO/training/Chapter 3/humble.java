/*
ID: ssk49881
LANG: JAVA
TASK: humble
*/

import java.io.*;
import java.util.*;

public class humble {
    public static void main(String[] args) throws Exception {
        // long start_time = System.currentTimeMillis();
        Scanner in = new Scanner(new File("humble.in"));
        PrintWriter out = new PrintWriter(new File("humble.out"));

        String phrase = in.nextLine();
        int numPrimes = Integer.parseInt(phrase.split(" ")[0]);
        int numHumbles = Integer.parseInt(phrase.split(" ")[1]);
        phrase = in.nextLine();
        int[] primes = new int[numPrimes];
        for (int i = 0; i < numPrimes; i++) {
            primes[i] = Integer.parseInt(phrase.split(" ")[i]);
        }
        int[] humbles = new int[numHumbles + 1];
        int[] nextMult = new int[numPrimes];
        humbles[0] = 1;

        for (int i = 1; i <= numHumbles; i++) {
            int max = Integer.MAX_VALUE;
            for (int j = 0; j < nextMult.length; j++) {
                while (primes[j] * humbles[nextMult[j]] <= humbles[i - 1]) {
                    nextMult[j]++;
                }
                if (max > primes[j] * humbles[nextMult[j]]) {
                    max = primes[j] * humbles[nextMult[j]];
                }
            }
            humbles[i] = max;
        }
        out.println(humbles[numHumbles]);

        /*
         * ArrayList<Long> humbles = new ArrayList<>(); ArrayList<Boolean> inTree = new
         * ArrayList<>(); int humbleCounter = 0;
         * 
         * int prevIndex = 0; humbles.add((long) 1); inTree.add(false); while
         * (humbleCounter < numHumbles + 1) { for (int i = prevIndex; i < inTree.size();
         * i++) { if (!inTree.get(i)) { if (humbleCounter % 5000 == 0) {
         * System.out.println( humbleCounter + " " + humbles.size() + " " +
         * (System.currentTimeMillis() - start_time)); } prevIndex = i; inTree.set(i,
         * true); long num = humbles.get(i); for (int j = 0; j < numPrimes; j++) { if
         * (humbles.size() > numHumbles + 10 && num * primes[j] > humbles.get(numHumbles
         * + 1)) { continue; }
         * 
         * int index; if (num * primes[j] > humbles.get(humbles.size() - 1)) { index =
         * humbles.size(); } else { index = Collections.binarySearch(humbles, num *
         * primes[j]); if (index >= 0) { continue; } else { index = -1 * (index + 1); }
         * } if (index < numHumbles + 10) { inTree.add(index, false); humbles.add(index,
         * num * primes[j]); }
         * 
         * } humbleCounter++; break; } } } out.println(humbles.get(numHumbles));
         */
        in.close();
        out.close();
    }
}