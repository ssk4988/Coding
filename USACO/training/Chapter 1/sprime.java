/*
ID: ssk49881
LANG: JAVA
TASK: sprime
*/

import java.io.*;
import java.util.*;

public class sprime {
    public static ArrayList<Integer> primes = new ArrayList<>();
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("sprime.in"));
        PrintWriter out = new PrintWriter(new File("sprime.out"));
        int n = Integer.parseInt(in.nextLine());
        ArrayList<Integer> superprimes = new ArrayList<>();
        superprimes.add(2);
        superprimes.add(3);
        superprimes.add(5);
        superprimes.add(7);
        int[] expandDigits = {1, 3, 7, 9};
        for (int i = 2; i < 100; i++) {
            isPrime(i);
        }
        for(int i = 1; i < n; i++){
            ArrayList<Integer> newsupers = new ArrayList<>();
            for(int superprime: superprimes){
                for(int enddigit : expandDigits){
                    if(isPrime(10 * superprime + enddigit)){
                        newsupers.add(10 * superprime + enddigit);
                    }
                }
            }
            superprimes = newsupers;
        }
        for(int superprime:superprimes){
            System.out.println(superprime);
            out.println(superprime);
        }

        in.close();
        out.close();
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