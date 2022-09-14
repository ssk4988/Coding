// Arup Guha
// 8/29/2022
// Solution to 2022 UCF Locals Final Round Problem: House Prices Going Up

import java.util.*;

public class house {

	public static void main(String[] args) {
		
		// Set up bit.
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		bit myb = new bit(n);
		
		// Put in each house price.
		for (int i=0; i<n; i++) 
			myb.add(i+1, stdin.nextLong());
		
		int numQ = stdin.nextInt();
		
		// Process queries.
		for (int i=0; i<numQ; i++) {
			
			// Get operation.
			char op = stdin.next().charAt(0);
			
			// Query.
			if (op == 'R') {
				int lowI = stdin.nextInt();
				int highI = stdin.nextInt();
				System.out.println(myb.query(lowI, highI));
			}
			
			// Add value.
			else {
				int loc = stdin.nextInt();
				long add = stdin.nextLong();
				myb.add(loc, add);
			}
		}
	}
}

// My binary index tree...
class bit {

	public int n;
	public long[] freq;

	// bit is from 1..myn.
	public bit(int myn) {
		n = 1;
		while (n<myn+1) n<<=1;
		freq = new long[n];
	}
	
	// Adds val to index idx.
	public void add(int idx, long val) {
		while (idx<n) {
			freq[idx] += val;
			idx += (idx&(-idx));
		}
	}
	
	// Returns sum from index 1 to idx.
	public long sum(int idx) {
		long res = 0;
		while (idx > 0) {
			res += freq[idx];
			idx -= (idx&(-idx));
		}
		return res;
	}
	
	// Returns sum of values from index lowI to index highI, inclusive.
	public long query(int lowI, int highI) {
		return sum(highI)-sum(lowI-1);
	}
}