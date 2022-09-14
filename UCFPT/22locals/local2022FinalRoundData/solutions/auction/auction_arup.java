// Arup Guha
// 8/27/2022
// Alternate Solution to 2022 UCF Locals Final Round Problem: Share Auction

import java.util.*;
import java.io.*;

public class auction_arup {

	public static int n;
	public static long v;
	public static long[] profit;
	public static long[] vouchers;
	
	public static void main(String[] args) {
	
		Scanner stdin = new Scanner(System.in);
		n = stdin.nextInt();
		v = stdin.nextLong();
		profit = new long[n];
		vouchers = new long[n];
		
		for (int i=0; i<n; i++) {
			profit[i] = stdin.nextLong();
			vouchers[i] = stdin.nextLong();
		}
		
		// We'll have to figure out our low and high (for the binary search) looking through the data.
		double low = 0;
		double high = 0;
		
		for (int i=0; i<n; i++) {
			high = Math.max(high, .5*profit[i]);
			low = Math.max(low, (1.0*v/(vouchers[i]+v) - 1.0*(v-1)/(vouchers[i]+v-1))*profit[i]);
		}
		
		// Here we binary search the cost of the least efficient voucher bought.
		for (int i=0; i<100; i++) {
		
			double mid = (low+high)/2;
			
			// This is how many vouchers we buy if we buy all that gain us at least mid in expectation.
			long numV = eval(mid);
			
			// This means we bought too many and our cut point is a higher number.
			if (numV > v) 
				low = mid;
			
			// We didn't get enough, so our cut point is lower.
			else
				high = mid;
		}
		
		// So for this value of low, I get how many vouchers I bought and my expected profit.
		long bought = eval(low);
		double ans = getExp(low);
		
		// Super tricky case...luckily it was in the sample. So basically, there could be multiple vouchers at this lowest value.
		// If there are, then we might overbuy, since we try to buy ALL vouchers at that price. So, subtract out all the ones that
		// are over our limit. This is pretty hacky, and I am pretty sure you can break it due to precision issues.
		if (bought > v) ans -= ((bought-v)*low);
		
		// Ta da!
		System.out.println(ans);
	}
	
	// Returns the expected profit if we buy all vouchers that add at least minVal to our expected value.
	public static double getExp(double minVal) {
	
		double res = 0;
		for (int i=0; i<n; i++) {
		
			// What our fraction must be equal to.
			double fraction = minVal/profit[i];
			
			// This is how many vouchers we must buy.
			long maxX = getMaxX(vouchers[i], fraction);
			
			// Here is how much money they yield us.
			res += (1.0*profit[i]*maxX)/(vouchers[i]+maxX);
		}
		
		return res;
	}	
	
	// Returns the number of vouchers we buy if we buy all that gain us at least minVal profit.
	public static long eval(double minVal) {
	
		long res = 0;
		for (int i=0; i<n; i++) {
		
			// What our fraction must be equal to.
			double fraction = minVal/profit[i];
			
			// Binary search the maximum value of x which satisfies the inequality.
			long maxX = getMaxX(vouchers[i], fraction);
			res += maxX;
		}
		
		// Ta da!
		return res;
	}
	
	// Find max x for which numV/((x+numV) * (x+numV-1)) > frac
	public static long getMaxX(long numV, double frac) {
	
		// Equivalently, we want the max x for which (x+nV)(x+nV-1) < this value.
		double RHS = numV/frac;
		
		long low = 0, high = (long)RHS;
		
		while (low < high) {
			
			long mid = (low+high+1)/2;
			
			// This is what we need to be less than RHS.
			double tryVal = 1.0*(numV+mid)*(numV+mid-1);
			
			// Too big...
			if (tryVal >= RHS)
				high = mid-1;
			
			// We're good.
			else
				low = mid;
		}
		
		return low;
	}
}