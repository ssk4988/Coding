// Arup Guha
// 9/6/2022
// C++ Solution to 2022 UCF Locals Problem: Which Number, ported from my Java solution

using namespace std;

#include <iostream>

typedef long long ll;

// My globals.
int numP;
ll pList[14];

// Function prototypes.
ll count(ll x);
bool isDivisible(ll x);
int bitcount(int n);
	
int main(void) {

	// Read input.
	ll n;
	cin >> n >> numP;
	for (int i=0; i<numP; i++)
		cin >> pList[i]; 
	
	// Set bounds for binary search.
	ll low = 1, high = 1000000000000000000ll;
	while (isDivisible(high)) high++;
		
	// Run binary search.
	while (low < high) {
		
		// Get next and previous valid number to try.
		ll mid = (low+high)/2;
		ll next = mid, prev = mid-1;
		while (isDivisible(next)) next++;
		while (isDivisible(prev)) prev--;
			
		// Get how many #s Natasha says here.
		ll numValid = count(next);
			
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
	cout << low << endl;
}
	
ll count(ll x) {
	
	ll res = x;
		
	// Store products for each mask subset.
	ll* prod = new ll[1<<numP];
	prod[0] = 1;
		
	// Run inclusion-exclusion.
	for (int mask=1; mask<(1<<numP); mask++) {
		
		// Decide if we're adding or subtracting.
		int sign = bitcount(mask)%2 == 0 ? 1 : -1;
		
		// Lowest one bit.
		int bit = 0;
		while ((mask & (1<<bit)) == 0) bit++;
		
		// Update this product.
		prod[mask] = prod[mask-(1<<bit)]*pList[bit];
			
		// Number of terms in range divisible.
		ll tmp = x/prod[mask];
			
		// Add or subtract as needed.
		res += (sign*tmp);
	}
		
	delete [] prod;
	
	return res;
}
	
// Returns true iff x is divisible by one of the primes we are to avoid.
bool isDivisible(ll x) {
	for (int i=0; i<numP; i++)
		if (x%pList[i] == 0)
			return true;
	return false;
}

// Returns the number of bits in n set to 1. Assumes n >= 0.
int bitcount(int n) {
	int res = 0, i=0;
	while ((1<<i) <= n) {
		if (n&(1<<i)) res++;
		i++;
	}
	return res;
}