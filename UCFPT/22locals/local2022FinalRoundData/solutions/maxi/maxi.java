//
// 2022 UCF Local Programming Contest (Final Round) -- maxi
// Ali Orooji
//

import java.util.*;
import java.lang.Math;

public class maxi
{
	public static String num_str; // input number in string
	
	public static char num_char[]; // input number in char
	
	public static Scanner input;
	
   /* ********************************************************* */
	
   public static void main(String[] args)
   {
	  input = new Scanner(System.in);
	  
	  num_str = input.next();
	  solve();
	   
   }// end of main()

   /* ********************************************************* */
	
   public static void solve()
   {
	  num_char = new char[7];
	  
	  num_char = num_str.toCharArray();
	  Arrays.sort(num_char);
	  
	  // num_char is in increasing order; print it in reverse order
	  for (int k = num_str.length() - 1;  k >= 0;  --k)
		  System.out.print(num_char[k]);
	  
	  System.out.println();
	   
   }// end of solve()

   /* ********************************************************* */
 
}// end of class maxi

   /* ********************************************************* */
