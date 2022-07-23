/*
  revenge.java
  Pythagorean's Revenge, MCPC 2012 Problem A
  Java solution by Andy Harrington

  a^2 = c^2 - b^2 = (c-b)*(c+b)
  Look for factor a^2 = x*y, b = (y-x)/2 > a

  I use the bound on x when b=a,  solving for x = c-b = c-a so (c-a)(c+a) = a^2.
*/

import java.util.*;
import java.io.*;
import static java.lang.Math.*;

public class revenge
{
   
   public static void main(String[] args) throws Exception {
      Scanner in = new Scanner(new File("revenge.in"));
      int a  = in.nextInt();
      while (a  > 0) {
         long a2 = (long)a*a;
         int count = 0;
         for (long x = (long)((sqrt(2) - 1)*a); x > 0; x--)
            if (a2 % x == 0 && (a2/x - x) % 2 == 0)
               count++;
         System.out.println(count);
         a = in.nextInt();
      }
   }
}
