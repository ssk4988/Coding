// Arup Guha
// 8/9/2022
// Solution to 2022 UCF Locals Problem: Which Number

import java.util.*;

public class whichnum {
	
	public static int numP;
	public static long[] pList;
	
	public static void main(String[] args) {
	
		// Read input.
		Scanner stdin = new Scanner(System.in);
		long n = stdin.nextLong();
		numP = stdin.nextInt();
		pList = new long[numP];
		for (int i=0; i<numP; i++)
			pList[i] = stdin.nextLong();
		
		// Set bounds for binary search.
		long low = 1, high = 1000000000000000000L;
		while (isDivisible(high)) high++;
		
		// Run binary search.
		while (low < high) {
		
			// Get next and previous valid number to try.
			long mid = (low+high)/2;
			long next = mid, prev = mid-1;
			while (isDivisible(next)) next++;
			while (isDivisible(prev)) prev--;
			
			// Get how many #s Natasha says here.
			long numValid = count(next);
			
			// Must go higher.
			if (numValid < n)
				low = next+1;
				
			// Must go lower and we know it can't be higher than prev.
			else if (numValid > n)
				high = prev;
				
			// We're good. This will let us break out.	
			else 
				low = high = next;
		}
		
		// Ta da!
		System.out.println(low);
	}
	
	public static long count(long x) {
	
		long res = x;
		
		// Store products for each mask subset.
		long[] prod = new long[1<<numP];
		prod[0] = 1;
		
		// Run inclusion-exclusion.
		for (int mask=1; mask<(1<<numP); mask++) {
		
			// Decide if we're adding or subtracting.
			int sign = Integer.bitCount(mask)%2 == 0 ? 1 : -1;
			
			// Lowest one bit.
			int bit = 0;
			while ((mask & (1<<bit)) == 0) bit++;
			
			// Update this product.
			prod[mask] = prod[mask-(1<<bit)]*pList[bit];
			
			// Number of terms in range divisible.
			long tmp = x/prod[mask];
			
			// Add or subtract as needed.
			res += (sign*tmp);
		}
		
		return res;
	}
	
	// Returns true iff x is divisible by one of the primes we are to avoid.
	public static boolean isDivisible(long x) {
		for (Long p : pList)
			if (x%p == 0)
				return true;
		return false;
	}
}