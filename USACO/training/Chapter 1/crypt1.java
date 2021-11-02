/*
ID: ssk49881
LANG: JAVA
TASK: crypt1
*/

import java.io.*;
import java.util.*;

public class crypt1 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("crypt1.in"));
        PrintWriter out = new PrintWriter(new File("crypt1.out"));
        int n = Integer.parseInt(in.nextLine());
        String digits = "";
        int solutions = 0;
        for (int i = 0; i < n; i++) {
            digits += Integer.toString(in.nextInt());
        }
        for (char a : digits.toCharArray()) {
            int aint = Integer.parseInt(String.valueOf(a));
            if (aint == 0) {
                continue;
            }
            for (char b : digits.toCharArray()) {
                int bint = Integer.parseInt(String.valueOf(b));
                for (char c : digits.toCharArray()) {
                    int cint = Integer.parseInt(String.valueOf(c));
                    for (char d : digits.toCharArray()) {
                        int dint = Integer.parseInt(String.valueOf(d));
                        if (dint == 0) {
                            continue;
                        }
                        solution: for (char e : digits.toCharArray()) {
                            int eint = Integer.parseInt(String.valueOf(e));
                            int partialproduct1 = eint * (100 * aint + 10 * bint + cint);
                            if (Math.log10(partialproduct1) >= 3) {
                                continue;
                            }
                            int partialproduct2 = dint * (100 * aint + 10 * bint + cint);
                            if (Math.log10(partialproduct2) >= 3) {
                                continue;
                            }
                            int product = partialproduct1 + partialproduct2 * 10;
                            if (Math.log10(product) >= 4) {
                                continue;
                            }
                            for (char dig : Integer.toString(partialproduct1).toCharArray()) {
                                if (digits.indexOf(dig) == -1) {
                                    continue solution;
                                }
                            }
                            for (char dig : Integer.toString(partialproduct2).toCharArray()) {
                                if (digits.indexOf(dig) == -1) {
                                    continue solution;
                                }
                            }
                            for (char dig : Integer.toString(product).toCharArray()) {
                                if (digits.indexOf(dig) == -1) {
                                    continue solution;
                                }
                            }
                            solutions++;
                        }
                    }
                }
            }
        }
        out.println(solutions);

        in.close();
        out.close();
    }
}