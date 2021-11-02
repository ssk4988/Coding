/*
ID: ssk49881
LANG: JAVA
TASK: leftout
*/

import java.io.*;
import java.util.*;

public class leftout {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("leftout.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("leftout.out")));
        int dim = Integer.parseInt(in.readLine());
        boolean[][] state = new boolean[dim][dim];
        for (int i = 0; i < dim; i++) {
            String s = in.readLine();
            for (int j = 0; j < dim; j++) {
                state[i][j] = s.charAt(j) == 'L';
            }
        }
        ArrayList<Integer> rows = new ArrayList<>();
        for (int i = 0; i < dim; i++) {
            if (rows.size() == 3) {
                break;
            }
            boolean unique = true;
            for (int j = 0; j < rows.size(); j++) {
                int k = rows.get(j);
                if (same(state[k], state[i])) {
                    unique = false;
                    break;
                }
                // if(opposite(a1, a2))
            }
            if (unique) {
                rows.add(i);
            }
        }
        int ind1 = -1;
        int ind2 = -2;
        for (int i = 0; i < rows.size(); i++) {
            for (int j = i + 1; j < rows.size(); j++) {
                int i2 = rows.get(i);
                int j2 = rows.get(j);
                if (opposite(state[i2], state[j2])) {
                    ind1 = i2;
                    ind2 = j2;
                }
            }
        }
        ArrayList<Integer> l = new ArrayList<>();
        l.addAll(rows);
        l.remove((Integer) ind1);
        l.remove((Integer) ind2);
        int row = l.get(0);
        int opprow = -1;
        if (numSame(state[row], state[ind1]) == dim - 1) {
            opprow = ind1;
        } else if (numSame(state[row], state[ind2]) == dim - 1) {
            opprow = ind2;
        }
        if (opprow == -1 || rows.size() != 3 || ind1 == -1) {
            out.println(-1);
        } else {
            ArrayList<Integer> li = diff(state[row], state[opprow]);
            int col = li.get(0);
            if (li.size() > 1) {
                out.println(-1);
            } else {
                row++;
                col++;
                out.println(row + " " + col);
            }

        }

        in.close();
        out.close();
    }

    public static ArrayList<Integer> diff(boolean[] a1, boolean[] a2) {
        ArrayList<Integer> b = new ArrayList<>();
        for (int i = 0; i < a1.length; i++) {
            if (a1[i] != a2[i]) {
                b.add(i);
            }
        }
        return b;
    }

    public static int numSame(boolean[] a1, boolean[] a2) {
        int b = 0;
        for (int i = 0; i < a1.length; i++) {
            if (a1[i] == a2[i]) {
                b++;
            }
        }
        return b;
    }

    public static boolean same(boolean[] a1, boolean[] a2) {
        boolean b = true;
        for (int i = 0; i < a1.length; i++) {
            if (a1[i] != a2[i]) {
                b = false;
                break;
            }
        }
        return b;
    }

    public static boolean opposite(boolean[] a1, boolean[] a2) {
        boolean b = true;
        for (int i = 0; i < a1.length; i++) {
            if (a1[i] == a2[i]) {
                b = false;
                break;
            }
        }
        return b;
    }
}