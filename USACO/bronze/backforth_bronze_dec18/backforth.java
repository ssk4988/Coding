/*
ID: ssk49881
LANG: JAVA
TASK: backforth
*/

import java.io.*;
import java.util.*;

public class backforth {
    public static TreeSet<Integer> solutions;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("backforth.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("backforth.out")));

        solutions = new TreeSet<>();
        ArrayList<Integer>[] barn = new ArrayList[2];
        barn[0] = new ArrayList<>();
        barn[1] = new ArrayList<>();
        for (int i = 0; i < 2; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < 10; j++) {
                barn[i].add(Integer.parseInt(tokenizer.nextToken()));
            }
        }
        solve(barn, 1000, 0);
        out.println(solutions.size());

        in.close();
        out.close();
    }

    public static void solve(ArrayList<Integer>[] barn, int milk, int depth) {
        if (depth == 4) {
            solutions.add(milk);
        } else {
            int ind1 = depth % 2;
            for (int i = 0; i < barn[ind1].size(); i++) {
                int num = barn[ind1].remove(i);
                barn[1 - ind1].add(num);
                solve(barn, ind1 == 0 ? milk - num : milk + num, depth + 1);
                num = barn[1 - ind1].remove(barn[1 - ind1].size() - 1);
                barn[ind1].add(i, num);
            }
        }
    }
}