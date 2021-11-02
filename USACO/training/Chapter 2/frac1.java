/*
ID: ssk49881
LANG: JAVA
TASK: frac1
*/

import java.io.*;
import java.util.*;

public class frac1 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("frac1.in"));
        PrintWriter out = new PrintWriter(new File("frac1.out"));
        int n = Integer.parseInt(in.nextLine());
        ArrayList<Fraction> fractions = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (areCoPrime(i, j)) {
                    fractions.add(new Fraction(j, i));
                }
            }
        }
        Collections.sort(fractions);
        for (Fraction fraction : fractions) {
            out.println(fraction.toString());
        }
        in.close();
        out.close();
    }

    public static boolean areCoPrime(int num1, int num2) {
        if (num1 * num2 == 1) {
            return true;
        } else if (num1 == num2) {
            return false;
        } else if (num1 * num2 == 0) {
            return num1 + num2 == 1 ? true : false;
        } else if (!(Math.min(num1, num2) == 1) && Math.max(num1, num2) % Math.min(num1, num2) == 0) {
            return false;
        }
        for (int i = 2; i < Math.min(num1, num2); i++) {
            if (num1 % i == 0 && num2 % i == 0) {
                return false;
            }
        }

        return true;
    }
}

class Fraction implements Comparable<Fraction> {
    int numerator;
    int denominator;

    public Fraction(int num, int dom) {
        this.numerator = num;
        this.denominator = dom;
    }

    @Override
    public int compareTo(Fraction o) {
        if ((float) this.numerator / this.denominator - (float) o.numerator / o.denominator < 0) {
            return -1;
        } else if ((float) this.numerator / this.denominator - (float) o.numerator / o.denominator == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    public String toString() {
        return this.numerator + "/" + this.denominator;
    }
}