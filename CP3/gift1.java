/*
ID: ssk49881
LANG: JAVA
TASK: gift1
*/

import java.io.*;
import java.util.*;

public class gift1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;
        int times = 0;
        while ((line = in.readLine()).length() > 0) {
            if (times != 0)
                System.out.println("x"+times);
            int numPeople = Integer.parseInt(line);
            String[] friends = new String[numPeople];
            int[] money = new int[numPeople];
            int[] balance = new int[numPeople];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < numPeople; i++) {
                friends[i] = tokenizer.nextToken();
                balance[i] = 0;
            }
            for (int i = 0; i < numPeople; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                String name = tokenizer.nextToken();
                int index = Arrays.asList(friends).indexOf(name);
                String moneydonors = tokenizer.nextToken();
                money[index] = Integer.parseInt(moneydonors);
                int numdonors = Integer.parseInt(tokenizer.nextToken());
                String[] donors = new String[numdonors];
                for (int j = 0; j < numdonors; j++) {
                    donors[j] = tokenizer.nextToken();
                }
                for (int k = 0; k < numPeople; k++) {
                    if (Arrays.asList(donors).contains(friends[k])) {
                        balance[k] += money[index] / numdonors;
                        balance[index] -= money[index] / numdonors;
                    }
                }
            }
            for (int i = 0; i < numPeople; i++) {
                out.println(friends[i] + " " + Integer.toString(balance[i]));
            }
            times++;
        }
        in.close();
        out.close();
    }
}