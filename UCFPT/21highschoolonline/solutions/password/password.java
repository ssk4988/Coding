package solutions.password;

/**
 * Ryan Glaspey, 03/07/20
 * First Draft
 */ 

import java.util.*;
import java.io.*;

// The problem can be boiled down to the number of permutations (with repeats) of the digits 
// {0, 3, 6, 9} in list of length 'n'. The value of this is 4^n.
// 
// General Proof:
//====================================================================
// Remember the 3 divisibility trick: if the sum of the digits of a number is divisible by 3, 
// then the entire number is divisible by 3. Mini-proof of that below for integers of length 3:
// a + b + c = 3d (d in Z)
// abc = 100a+10b+c = 99a + a + 9b + b + c = (a + b + c) + 99a + 9b
// (a + b + c) + 99a + 9b = 3d + 99a + 9b = 3(d + 33a + 3b) = 3e (e in Z)
// abc = 3e, where e is any integer; 3 | abc
//
// Let S be a list of multiples of 3: {3a, 3b, 3c, ...} (a,b,c in Z) 
// The sum of all elements in the list is 3a + 3b + 3c
// 3a + 3b + 3c = 3(a + b + c) = 3d where d in Z because integers are closed on addition
// Therefore, 3 | the sum of all elements in the list
//
// Every nonempty substring of a valid password must be divisible by 3
// Every nonempty substring of length > 1 is composed of substrings of length 1
// Every substring of length 1 must be divisible by 3
// Every digit must be a multiple of 3: {0, 3, 6, 9}
// Every permutation of single-digit multiples of 3 will form a 2-digit multiple of 3 (see paragraph above)
// Likewise, any permutation of size n of single-digit multiples of 3 will form an n-digit multiple of 3 (see paragraph above)
// If all the digits of a number are divisible by 3, then any combination of them (any substring of the original number) is divisible by 3
// Therefore, the goal of the problem is to find every permutation of single-digit multiples of 3
public class password {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        int[] power4Table = new int[15+1];
        power4Table[0] = 1;
        for (int i = 1; i <= 15; i++) {
            power4Table[i] = power4Table[i-1] * 4;
        }
        while (t-->0) {
            int length = sc.nextInt();
            // 0 is not a valid input, so it does not need to be accounted for 
            // here; (4^0 = 1) != (0)
            System.out.println(power4Table[length]);
        }
    }
}