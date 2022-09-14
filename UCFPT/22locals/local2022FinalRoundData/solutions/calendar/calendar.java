//
// 2022 UCF Local Programming Contest (Final Round) -- calendar
// Ali Orooji
//

import java.util.*;
import java.lang.Math;

public class calendar
{
	public static int date[][]; /* date[][0] what day of the month
	                               date[][1] what month of the year
								   date[][2] what year
								   date[][3] what day of the week */
	
	public static int date_in_days[]; // date expressed in days 
	
	public static Scanner input;
	
   /* ********************************************************* */
	
   public static void main(String[] args)
   {
	  input = new Scanner(System.in);
	  
	  date = new int[2][4];
	  
	  date_in_days = new int[2];
	  
	  read_a_date(0);
	  date[0][3] = input.nextInt();
	  
	  read_a_date(1);
	  
	  solve();
	  System.out.println(date[1][3]);
	   
   }// end of main()

   /* ********************************************************* */
	
   public static void read_a_date(int date_index)
   {
	  // Read day, month, year.
	  
	  for (int k = 0;  k <= 2;  ++k)
		  date[date_index][k] = input.nextInt();
	   
   }// end of read_a_date()

   /* ********************************************************* */
	
   public static void solve()
   {
	  // find the total number of days in each date
	  for (int k = 0;  k <= 1;  ++k)
		  date_in_days[k] = find_date_in_days(k);
	  
	  // find how many days the second date is after the first date
	  int days_diff = date_in_days[1] - date_in_days[0];
	  
	  // remove weeks (multiples of 7)
	  days_diff = days_diff % 7;
	  
	  // find day of the week for the second date
	  date[1][3] = date[0][3] + days_diff;
	  if (date[1][3] > 7)
		  date[1][3] -= 7;
	   
   }// end of solve()

   /* ********************************************************* */
	
   public static int find_date_in_days(int date_index)
   {
	  // Find the total number of days for a date.
	  
	  int days_count = ((date[date_index][2] - 1000) * 360) +
	                   ((date[date_index][1] - 1   ) * 30 ) +
					   ((date[date_index][0] - 1   )      );
	  
	  return(days_count);
	   
   }// end of find_date_in_days()

   /* ********************************************************* */
 
}// end of class calendar

   /* ********************************************************* */
