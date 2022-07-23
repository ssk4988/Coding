package solutions.jenny;

/*

jenny.java
Precompute all possible Jenny numbers
Use a square root check for primality

*/

import java.util.*;

public class jenny {

    static ArrayList<Long>[] ans = new ArrayList[10];   // Stores all possible Jenny numbers
    static int d, k;                                    // d and k in input

    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);

        // Set up ans
        for (int i = 0; i < 10; i++) ans[i] = new ArrayList<>();

        // Run go
        go(0, 0, new boolean[10]);

        // Ensure answers are sorted
        for (int i = 0; i < 10; i++) Collections.sort(ans[i]);

        int t = stdin.nextInt();

        for (; t > 0; t--) {
            d = stdin.nextInt();
            k = stdin.nextInt();

            // Case out 10 digit and larger input
            if (d > 9) System.out.println("Brice doesn't stand a chance!");
            // Case out too high index
            else if (k > ans[d].size()) System.out.println("Brice doesn't stand a chance!");
            // Retrieve answer
            else System.out.println(ans[d].get(k-1));
        }
    }

    static void go(int indx, long curr, boolean[] used) {
        // If this current number is a jenny number, add it to the current length (kept in indx)
        if (isJenny(curr))
            ans[indx].add(curr);
        
        // Try all possibilities
        for (int i = 0; i < 10; i++) {
            // Can't have a leading zero
            if (indx == 0 && i == 0) continue;
            // If used, can't use again
            if (used[i]) continue;
            // Permute
            used[i] = true;
            go(indx+1, curr*10+i, used);    // Go to next index, update current number and pass current used array
            used[i] = false;
        }
    }

    static boolean isJenny(long n) {
        // 1 is not prime
        if (n == 1) return false;
        // 2 is prime and 3 is prime so 2 is a Jenny number
        if (n == 2) return true;
        // If n is divisible by 2 it is not prime
        if (n % 2 == 0) return false;
        // Check divisiblity of n and n+2 by all odds up to the square root of n+2
        for (long i = 3; i*i <= n+2; i+=2)
            if (n % i == 0 || (n+2) % i == 0) 
                return false;
        return true;
    }
}