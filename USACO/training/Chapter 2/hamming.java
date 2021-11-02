/*
ID: ssk49881
LANG: JAVA
TASK: hamming
*/

import java.io.*;
import java.util.*;

public class hamming {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("hamming.in"));
        PrintWriter out = new PrintWriter(new File("hamming.out"));
        String phrase = in.nextLine();
        int n = Integer.parseInt(phrase.split(" ")[0]);
        int b = Integer.parseInt(phrase.split(" ")[1]);
        int d = Integer.parseInt(phrase.split(" ")[2]);
        ArrayList<Integer> codewords = new ArrayList<>();
        Collections.fill(codewords, -3);
        for (int i = 0; i < Math.pow(2, b); i++) {
            boolean fits = true;
            for (int codeword : codewords) {
                if (hammingDistance(codeword, i) < d) {
                    fits = false;
                }
            }
            if (fits) {
                codewords.add(i);
                System.out.println(i);
            }
            if (codewords.size() >= n) {
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i % 10 == 9 || i == n - 1) {
                out.println(codewords.get(i));
            } else {
                out.print(codewords.get(i) + " ");
            }
        }

        in.close();
        out.close();
    }

    public static int hammingDistance(int num1, int num2) {
        String hammingBits = convertToBase(num1 ^ num2, 2);
        int distance = 0;
        for (char bit : hammingBits.toCharArray()) {
            if (bit == '1') {
                distance++;
            }
        }
        return distance;
    }

    public static String convertToBase(int num, int b) {
        String digits = "0123456789ABCDEFGHIJKLMNOP";
        String number = "";
        int copynum = num;
        for (int i = (int) (Math.floor(Math.log10(num) / Math.log10(b))); i >= 0; i--) {
            number += String.valueOf(digits.charAt((int) (Math.floor(copynum / Math.pow(b, i)))));
            copynum = copynum % (int) Math.pow(b, i);
        }
        return number;
    }
}