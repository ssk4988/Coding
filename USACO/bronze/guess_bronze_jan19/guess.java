/*
ID: ssk49881
LANG: JAVA
TASK: guess
*/

import java.io.*;
import java.util.*;

public class guess {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("guess.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("guess.out")));
        TreeMap<String, Integer> numTimes = new TreeMap<>();
        int numAnimals = Integer.parseInt(in.readLine());
        ArrayList<String>[] qualities = new ArrayList[numAnimals];
        for (int i = 0; i < numAnimals; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String animal = tokenizer.nextToken();
            int numqualities = Integer.parseInt(tokenizer.nextToken());
            qualities[i] = new ArrayList<>();
            for (int j = 0; j < numqualities; j++) {
                String quality = tokenizer.nextToken();
                if (!numTimes.containsKey(quality)) {
                    numTimes.put(quality, 0);
                }
                numTimes.put(quality, numTimes.get(quality) + 1);
                qualities[i].add(quality);
            }
        }
        int maxTimes = 0;
        for (int i = 0; i < numAnimals; i++) {
            for (int j = 0; j < i; j++) {
                ArrayList<String> clone = (ArrayList<String>) qualities[i].clone();
                clone.retainAll(qualities[j]);
                if (clone.size() > maxTimes)
                    maxTimes = clone.size();
            }
        }
        out.println(maxTimes + 1);

        in.close();
        out.close();
    }
}