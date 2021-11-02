/*
ID: ssk49881
LANG: JAVA
TASK: badmilk
*/

import java.io.*;
import java.util.*;

public class badmilk {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("badmilk.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("badmilk.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numFriends = Integer.parseInt(tokenizer.nextToken());
        int numMilk = Integer.parseInt(tokenizer.nextToken());
        int numDrinks = Integer.parseInt(tokenizer.nextToken());
        int numSick = Integer.parseInt(tokenizer.nextToken());
        ArrayList<Pair>[] drinks = new ArrayList[numFriends];
        TreeSet<Integer>[] drinks2 = new TreeSet[numMilk];
        for (int i = 0; i < numFriends; i++) {
            drinks[i] = new ArrayList<>();
        }
        for (int i = 0; i < numMilk; i++) {
            drinks2[i] = new TreeSet<>();
        }
        for (int i = 0; i < numDrinks; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int friend = Integer.parseInt(tokenizer.nextToken()) - 1;
            int milk = Integer.parseInt(tokenizer.nextToken()) - 1;
            int time = Integer.parseInt(tokenizer.nextToken());
            drinks[friend].add(new Pair(milk, time));
            drinks2[milk].add(friend);
        }
        TreeSet<Integer> drank = new TreeSet<>();
        for (int i = 0; i < numSick; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int friend = Integer.parseInt(tokenizer.nextToken()) - 1;
            int time = Integer.parseInt(tokenizer.nextToken());
            TreeSet<Integer> friendDrank = new TreeSet<>();
            for (Pair j : drinks[friend]) {
                if (j.time < time) {
                    friendDrank.add(j.milk);
                }
            }
            if (i == 0) {
                drank = friendDrank;
            } else {
                drank.retainAll(friendDrank);
            }
        }
        TreeSet<Integer> sick = new TreeSet<>();
        for (int m : drank) {
            sick.addAll(drinks2[m]);
        }
        out.println(sick.size());

        in.close();
        out.close();
    }
}

class Pair {
    int time;
    int milk;

    public Pair(int milk, int time) {
        this.time = time;
        this.milk = milk;
    }
}