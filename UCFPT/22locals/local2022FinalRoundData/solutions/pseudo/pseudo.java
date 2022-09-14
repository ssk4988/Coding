// Arup Guha
// 8/9/2022
// Solution to UCF Locals Problem: Pseudo Pseudo Random Numbers

import java.util.*;

public class pseudo {

	public static void main(String[] args) {
	
		// Get input.
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		int k = stdin.nextInt();
		
		int res = 0;
		
		// Go through all choices.
		for (int i=0; i<(1<<n); i++)
			if (maxRun(i, n) <= k)
				res++;
				
		// Ta da!
		System.out.println(res);
	}
	
	// Returns the max run of the same bit in n when represented with bits # of bits.
	public static int maxRun(int n, int bits) {
	
		// Go through each bit.
		int curRun = 0, maxRun = 0, curBit = -1;
		for (int i=0; i<bits; i++) {
		
			// Get this bit.
			int bit = (n & (1<<i)) == 0 ? 0 : 1;
			
			// New streak.
			if (bit != curBit) {
				curRun = 1;
				curBit = bit;
			}
			
			// Extend old streak.
			else
				curRun++;
				
			// Update max if necessary.
			maxRun = Math.max(maxRun, curRun);
		}
		
		return maxRun;
	}
}