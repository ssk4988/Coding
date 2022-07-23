/*
  digits.java
  Digit Solitaire, MCPC 2012 Problem B
  Java solution by Michael Goldwasser
*/

import java.util.*;
import java.io.*;

class digits {

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("digits.in"));

        while (true) {
            int v  = in.nextInt();
            if (v == 0) break;
            System.out.print(v);                   // initial number; no space
            while (v > 9) {
                // compute the product
                int product = 1;
                while (v > 0) {
                    product *= v % 10;
                    v /= 10;
                }
                System.out.print(" " + product);   // note leading space
                v = product;
            }
            System.out.println();                  // newline character
        }
    }
}
