/*
  bounce.java
  Bounce, MCPC 2012 Problem H
  Java solution by Andy Harrington

  given r, c, p, find seq with integral repetitions of first p char,
  with first and last at top, somewhere on bottom.
  p is 2 - 5
  r = 4 - ?
  c = 2 - ?
*/

import java.util.*;
import java.io.*;

public class bounce
{
   static char[][] hex; // input pattern
   static char[] seq;  // current proposed soluton sequence
   static int p;    // period
   // offsets to neighbors:
   static int[][] dc = { {1,  0, -1, -1, -1, 0},   // in even row
                         {1,  1,  0, -1,  0, 1} }; // in odd row
   static int[] dr =     {0, -1, -1,  0,  1, 1};   // in each row
   static char DONE = '\0';  // initial array value
   static int rHigh;
   static int nMax;
   static int nSol;
   static int nCall;
   static int[][] coord;

   
   public static void main(String[] args) throws Exception {
      String file = (args.length > 0) ? args[0] : "bounce.in";
      Scanner in = new Scanner(new File(file));
      rHigh  = in.nextInt();
      while (rHigh  > 0) {
         int c = in.nextInt();
         p = in.nextInt();
         hex = new char[rHigh+2][c+3]; // leave border; no boundary checks
         for (int i = 1; i <= rHigh; i++) { 
            for (int j = 1; j <= c + 1 - i % 2; j++) {
               hex[i][j] = in.next().toUpperCase().charAt(0);
               System.err.print(hex[i][j]);
            }
            System.err.println();
         }
         nMax = (rHigh*c + rHigh/2)/p*p;
         seq = new char[nMax]; 
         coord = new int[nMax][];
         nCall = nSol = 0;
         for (int j = 1; j < c; j++) 
            solve(1, j, j, 0, false);
         if (nSol == 0) // judge check
            System.out.println("no solution");
         System.err.println(nCall + " calls");
         rHigh = in.nextInt();
      }
   }

   // use hex[r][c] next if not max length.
   //   n char before; n is current length of seq without hex[r][c]
   static void solve(int r, int c, int startc, int n, boolean hitBottom) {
      char ch = hex[r][c];
      nCall++;
      if (ch == DONE) return;
      if (n >= p && ch != seq[n-p]) return; 
      seq[n] = ch;
      coord[n] = new int[]{r-1, c-1};
      hitBottom = hitBottom || r == rHigh;
      n++;
      if (hitBottom && r == 1 && n % p == 0 && n >= 2*p && startc < c) {
         for (int i = 0; i < n; i++)
            System.out.print(seq[i]);
         System.out.println();
         for (int i = 0; i < n; i++)
            System.err.print(String.format("(%s, %s), ", 
                                            coord[i][0], coord[i][1]));
         System.err.println();
         if (nMax == n)
            nSol++;
         else {
           nMax = n;
           nSol = 1;
         }
         return;
      }
      if (n == nMax) return;
      // recursion after here - must undo afterward
      hex[r][c] = DONE;  // don't let path come back here
      for (int i = 0; i < 6; i++) //
         solve(r + dr[i], c + dc[r%2][i], startc, n, hitBottom);
      hex[r][c] = ch; // revert to previous state for backtracking
   }
}
