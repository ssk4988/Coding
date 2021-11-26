package solutions.miracle;

import java.util.*;
import java.io.*;

public class miracle
{
   public static void main(String[] args)
   {
      // Read number of cases
      Scanner scan = new Scanner(System.in);
      int t = scan.nextInt();

      // Loop over cases
      for (int q = 1; q <= t; q++)
      {
         // Read the n values
         double h = 100.00;
         int n = scan.nextInt();
         for (int i = 0; i < n; i++)
         {
            int x = scan.nextInt();

            // Adjust level
            h += (h/100)*x;
         }

         // Output answer
         System.out.printf("%.7f%n", h-100);
      }
   }
}
