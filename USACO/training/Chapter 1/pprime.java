/*
ID: ssk49881
LANG: JAVA
TASK: pprime
*/

import java.io.*;
import java.util.*;

public class pprime {
    public static ArrayList<Integer> primes = new ArrayList<>();

    public static void main(String[] args) throws Exception {

        Scanner in = new Scanner(new File("pprime.in"));
        PrintWriter out = new PrintWriter(new File("pprime.out"));
        String phrase = in.nextLine();
        int a = Integer.parseInt(phrase.split(" ")[0]);
        int b = Integer.parseInt(phrase.split(" ")[1]);
        for (int i = 2; i < 100; i++) {
            isPrime(i);
        }
        for (int palindrome : generatePalindromes(a, b)) {
            if (isPrime(palindrome)) {
                System.out.println(palindrome);
                out.println(palindrome);
            }
        }

        in.close();
        out.close();

    }

    public static ArrayList<Integer> generatePalindromes(int start, int end) {
        ArrayList<Integer> palindromes = new ArrayList<>();
        int mindigits = String.valueOf(start).length();
        int maxdigits = String.valueOf(end).length();
        for (int numDigits = mindigits; numDigits <= maxdigits; numDigits++) {
            for (int stem : generateNumberswithDigits(Math.round((float) numDigits / 2))) {
                char[] numberArray = new char[numDigits];
                String stemString = Integer.toString(stem);
                for (int i = 0; i < stemString.length(); i++) {
                    numberArray[i] = stemString.charAt(i);
                    numberArray[numDigits - 1 - i] = stemString.charAt(i);
                }
                int number = Integer.parseInt(String.valueOf(numberArray));
                if (number >= start && number <= end) {
                    palindromes.add(number);
                }
            }
        }

        return palindromes;
    }

    public static ArrayList<Integer> generateNumberswithDigits(int numDigits) {
        ArrayList<Integer> numbers = new ArrayList<>();
        for (int i = (int) (Math.pow(10, numDigits - 1)); i < Math.pow(10, numDigits); i++) {
            numbers.add(i);
        }
        return numbers;
    }

    public static boolean isPal(int input) {
        String num = Integer.toString(input);
        boolean matches = true;
        if (num.length() == 1) {
            return true;
        }
        for (int i = 0; i < num.length() - 1 - i; i++) {
            if (num.charAt(i) != num.charAt(num.length() - 1 - i)) {
                matches = false;
            }
        }
        return matches;
    }

    public static boolean isPrime(int input) {
        if (primes.contains(input)) {
            return true;
        }
        for (int prime : primes) {
            if (input % prime == 0) {
                return false;
            }
        }
        if (input % 2 == 0) {
            return false;
        }

        for (int i = 3; i <= Math.sqrt(input); i += 2) {
            if (input % i == 0) {
                return false;
            }
        }
        if (!primes.contains(input)) {
            primes.add(input);
        }
        return true;
    }
}