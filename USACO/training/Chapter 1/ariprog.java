/*
ID: ssk49881
LANG: JAVA
TASK: ariprog
*/

import java.io.*;
import java.util.*;

public class ariprog {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("ariprog.in"));
        PrintWriter out = new PrintWriter(new File("ariprog.out"));
        int n = Integer.parseInt(in.nextLine()); // length
        int m = Integer.parseInt(in.nextLine()); // max value of x,y in x^2 + y^2
        int maxbisquare = (int) (2 * Math.pow(m, 2));
        boolean[] bisquares = new boolean[maxbisquare + 1];
        ArrayList<sequence> sequences = new ArrayList<>();
        int numbisquares = 0;
        int bisquare;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= i; j++) {
                bisquare = (int) (Math.pow(i, 2) + Math.pow(j, 2));
                bisquares[bisquare] = true;
                numbisquares++;
            }
        }
        System.out.println(numbisquares);
        for (int a = 0; a < maxbisquare; a++) {
            if(!bisquares[a]){
                continue;
            }
            sequence: for (int b = 1; (maxbisquare - a) / (n - 1) >= b; b++) {
                for (int k = 0; k < n; k++) {
                    if (!bisquares[a + k * b]) {
                        continue sequence;
                    }
                }
                System.out.println(Integer.toString(a) + " " + Integer.toString(b));
                sequences.add(new sequence(a, b));
            }
        }
        Collections.sort(sequences);
        for (sequence sequence : sequences) {
            out.println(Integer.toString(sequence.a) + " " + Integer.toString(sequence.b));
        }
        if (sequences.size() == 0) {
            out.println("NONE");
        }

        in.close();
        out.close();
    }
}

class sequence implements Comparable<sequence> {
    public int a;
    public int b;

    public sequence(int a, int b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public int compareTo(sequence o) {
        return this.b - o.b == 0 ? this.a - o.a : this.b - o.b;
    }
}