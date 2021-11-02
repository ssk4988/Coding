/*
ID: ssk49881
LANG: JAVA
TASK: wormhole
*/

import java.io.*;
import java.util.*;

public class wormhole {
    public static ArrayList<int[]> pairlist = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("wormhole.in"));
        PrintWriter out = new PrintWriter(new File("wormhole.out"));
        int n = Integer.parseInt(in.nextLine());
        Hole[] wormholes = new Hole[n];
        Hole hole;
        int[] pairs = new int[n];
        int numSolutions = 0;
        for (int i = 0; i < n; i++) {
            String phrase = in.nextLine();
            int x = Integer.parseInt(phrase.split(" ")[0]);
            int y = Integer.parseInt(phrase.split(" ")[1]);
            hole = new Hole(x, y);
            wormholes[i] = hole;
        }
        for (int i = 0; i < wormholes.length; i++) {
            for (int j = 0; j < wormholes.length; j++) {
                if (i == j) {
                    continue;
                }
                if (wormholes[i].y == wormholes[j].y && wormholes[i].x < wormholes[j].x) {
                    if (wormholes[i].right == null) {
                        wormholes[i].right = wormholes[j];
                    } else if (wormholes[j].x < wormholes[i].right.x) {
                        wormholes[i].right = wormholes[j];
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            pairs[i] = i;
        }
        permute(pairs, 0);
        for (int[] intlist : pairlist) {
            System.out.println(intlist);
            for (int i = 0; i < intlist.length; i++) {
                wormholes[i].pair = wormholes[intlist[i]];
                wormholes[intlist[i]].pair = wormholes[i];
            }
            check: for (int i = 0; i < n; i++) {
                ArrayList<String> seen = new ArrayList<>();
                Hole currentHole = wormholes[i];
                while (currentHole.right != null) {
                    seen.add(currentHole.toString());
                    currentHole = currentHole.right.pair;
                    if (seen.contains(currentHole.toString())) {
                        numSolutions++;
                        System.out.println("works");
                        break check;
                    }

                }
            }
        }
        out.println(numSolutions);

        in.close();
        out.close();
    }

    public static void permute(int[] intarray, int index) {
        if (index == intarray.length - 1) {
            pairlist.add(intarray.clone());
        }
        int tmp;
        for (int i = index; i < intarray.length; i++) {
            if (intarray[index] == i) {
                continue;
            }
            tmp = intarray[index];
            intarray[index] = intarray[i];
            intarray[i] = tmp;
            if (intarray[intarray[i]] == i) {
                permute(intarray, index + 1);
            }
            tmp = intarray[index];
            intarray[index] = intarray[i];
            intarray[i] = tmp;
        }
    }
}

class Hole implements Comparable<Hole> {
    public int x;
    public int y;
    public Hole pair;
    public Hole right = null;

    public Hole(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(Hole o) {
        return this.x - o.x;
    }

    public String toString() {
        return Integer.toString(this.x) + "," + Integer.toString(this.y);
    }
}