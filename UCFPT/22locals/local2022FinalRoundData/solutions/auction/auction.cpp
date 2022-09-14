// Arup Guha
// 9/6/2022
// C++ Solution to 2022 UCF Locals Final Round Problem: Share Auction

using namespace std;

#include <iostream>
#include <cmath>
#include <iomanip>

typedef long long ll;

typedef struct answer {
	double exp;
	ll vUsed;
} answer;

#define MAX(a,b) ((a) > (b) ? a : b)

// Function prototypes.
answer getExp(double minVal);
ll getMaxX(ll numV, double prof, double minVal);

// My globals.
int n;
ll v;
ll* profit;
ll* vouchers;

int main(void) {

	// Read input.
	cin >> n >> v;
	profit = new ll[n];
	vouchers = new ll[n];
	for (int i=0; i<n; i++)
		cin >> profit[i] >> vouchers[i];

	// Set low, high for binary search of least efficient voucher.
	double low = 0, high = 0;
	for (int i=0; i<n; i++) {
		high = MAX(high, .5*profit[i]);
		low = MAX(low, (1.0*v/(vouchers[i]+v) - 1.0*(v-1)/(vouchers[i]+v-1))*profit[i]);
	}	
	
	// Run binary search.
	for (int i=0; i<100; i++) {
			
		double mid = (low+high)/2;
			
		// This is how many vouchers we buy if we buy all that gain us at least mid in expectation.
		ll numV = getExp(mid).vUsed;
			
		// This means we bought too many and our cut point is a higher number.
		if (numV > v) 
			low = mid;
			
		// We didn't get enough, so our cut point is lower.
		else
			high = mid;
	}
	
	// So for this value of low, I get how many vouchers I bought and my expected profit.
	answer res = getExp(low);
	
	// Super tricky case...luckily it was in the sample. So basically, there could be multiple vouchers at this lowest value.
	// If there are, then we might overbuy, since we try to buy ALL vouchers at that price. So, subtract out all the ones that
	// are over our limit. This is pretty hacky, and I am pretty sure you can break it due to precision issues.
	if (res.vUsed > v) res.exp -= ((res.vUsed-v)*low);
		
	// Ta da!
	cout << setprecision(13) << res.exp << endl;	

	delete [] profit;
	delete [] vouchers;
	return 0;
}

// Returns the expected profit if we buy all vouchers that add at least minVal to our expected value.
answer getExp(double minVal) {
	
	// Store everything we need to return here.
	answer res;
	res.exp = 0;
	res.vUsed = 0;
		
	// Go through each iten.
	for (int i=0; i<n; i++) {
			
		// This is how many vouchers we must buy.
		ll maxX = getMaxX(vouchers[i], profit[i], minVal);
		res.vUsed += maxX;
			
		// Here is how much money they yield us.
		res.exp += (1.0*profit[i]*maxX)/(vouchers[i]+maxX);
	}

	return res;
}

// Returns the max number of vouchers given that there are numV other vouchers, and the profit is prof and I want to make at least
// minVal per voucher I put in.
ll getMaxX(ll numV, double prof, double minVal) {
	
	// Binary search # of vouchers for this item.
	ll low = 0, high = 1000000001ll;
		
	while (low < high) {
			
		ll mid = (low+high+1)/2;
			
		// This is what we need to be less than RHS.
		double LHS = prof*(1.0*mid/(numV+mid) - 1.0*(mid-1)/(numV+mid-1));
			
		// Too big...
		if (LHS < minVal)
			high = mid-1;
			
		// We're good.
		else
			low = mid;
	}
		
	return low;
}
