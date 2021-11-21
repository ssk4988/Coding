/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class j {
    public static ArrayList<Knight> removeNext = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        Knight[] knights = new Knight[2 * n];
        for (int i = 0; i < knights.length; i++) {
            knights[i] = new Knight(i);
        }
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            int k = Integer.parseInt(tokenizer.nextToken()) - 1;
            knights[i].attack = knights[k];
            knights[k].numChallengers++;
        }
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = n; i < 2 * n; i++) {
            int k = Integer.parseInt(tokenizer.nextToken()) - 1;
            knights[i].attack = knights[k];
            knights[k].numChallengers++;
        }
        Set<Knight> kernel = new HashSet<>();
        Set<Knight> unused = new HashSet<>();
        Set<Knight> other = new HashSet<>();
        for (int i = 0; i < knights.length; i++) {
            unused.add(knights[i]);
        }
        while (unused.size() > 0) {
            if (removeNext.size() == 0) {
                for (Knight k : unused) {
                    if (k.numChallengers == 0) {
                        removeNext.add(k);
                    }
                }
            }
            if (removeNext.size() == 0) {
                for (Knight k : unused) {
                    removeNext.add(k);
                    break;
                }
            }
            for (int i = 0; i < removeNext.size(); i++) {
                addKernel(removeNext.get(i), kernel, unused, other);
            }
            removeNext = new ArrayList<>();
            // for (Knight k : unused) {
            // System.out.println("unused: " + k.id + " out of " + unused.size());
            // }

        }
        ArrayList<Integer> indices = new ArrayList<>();
        for (Knight k : kernel) {
            indices.add(k.id + 1);
        }
        Collections.sort(indices);
        for (int i = 0; i < indices.size(); i++) {
            System.out.print(indices.get(i));
            if (i < indices.size() - 1) {
                System.out.print(" ");
            }
        }
        System.out.println();

        in.close();
        out.close();
    }
    public static void addKernel(Knight k, Set<Knight> kernel, Set<Knight> unused, Set<Knight> other) {
        kernel.add(k);
        // System.out.println("kernel : " + k.id);
        unused.remove(k);
        k.unused = false;
        k.kernel = true;
        if (k.attack.unused) {
            other.add(k.attack);
            unused.remove(k.attack);
            // System.out.println("other: " + k.attack.id);
            k.attack.unused = false;
            k.attack.attack.numChallengers--;
            if (k.attack.attack.numChallengers == 0) {
                removeNext.add(k.attack.attack);
            }
        }
    }

    public static class Knight {
        int id;
        boolean unused = true;
        boolean kernel = false;
        int numChallengers = 0;
        Knight attack;

        public Knight(int id) {
            this.id = id;
        }
    }
}