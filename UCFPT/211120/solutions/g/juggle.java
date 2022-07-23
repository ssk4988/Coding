/*
  juggle.java
  JuggleFest, MCPC 2012 Problem G
  Java solution by Andy Harrington
*/

import java.io.*;
import java.util.*;

public class juggle
{   
   static int p;
   static int[] seq;
   static int MAX=20;
   
   public static void main(String[] args) throws Exception {
      String file = (args.length > 0) ? args[0] : "juggle.in";
      Scanner in = new Scanner(new File(file));
      p  = in.nextInt();
      while (p  > 0) {
        seq = new int[p]; 
        for (int i = 0; i < p; i++)  
           seq[i] = in.nextInt();
        System.out.println(solve());
        p = in.nextInt();
      }
   }

   static String solve() {
      char[] toss = new char[MAX];
      char ch = 'A';
      for (int i = 0; i < MAX; i++) {
         if (toss[i] == 0)
            toss[i] = ch++;
         int hi = i + seq[i % p];
         if (hi < 20)
            if ( toss[hi] != 0)
               return "CRASH";
            else
               toss[hi] = toss[i];    
      }
      return new String(toss);
   }
}
