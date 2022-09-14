// Arup Guha
// 9/6/2022
// C++ Solution to 2022 UCF Locals Qualifying Problem: Word Tree

using namespace std;

#include <iostream>
#include <queue>
#include <string>
#include <cmath>

#define MAX(a,b) ((a) > (b) ? a : b)

struct edge {
    int u,v,cost;
	
    bool operator<(const edge& other) const {
        return other.cost < cost;
    }
};

// Other globals I use.
int n, k;
string* words;

// Function prototypes.
int cost(int i, int j);

int main(void) {
	
	cin >> n >> k;
	words = new string[n];
	for (int i=0; i<n; i++)
		cin >> words[i];
		
	// Set up visited array for Prim's
	bool* used = new bool[n];
	for (int i=0; i<n; i++) used[i] = false;
	used[0] = true;
	
	// Set up PQ for Prim's.
	priority_queue<edge> pq;
	for (int i=1; i<n; i++) pq.push(edge{0,i,cost(0, i)});	
	
	// Will store our result.
	int res = 0, numV = 1;
	
	// While we're not connected.
	while (numV < n) {
	
		edge cur = pq.top();
		pq.pop();
		
		// Not to a new place.
		if (used[cur.u] && used[cur.v]) continue;
		
		// The new place.
		int newV = used[cur.u] ? cur.v : cur.u;
	
		// Bookkeeping - update result, used vertices & num vertices.
		res = MAX(res, cur.cost);
		used[newV] = true;
		numV++;
		
		// Add all edges incident to newV to pq.
		for (int i=0; i<n; i++) {
			if (i == newV) continue;
			pq.push(edge{newV,i,cost(newV,i)});
		}
	}
	
	// Ta da!
	cout << res << endl;
	
	// Clean up!
	delete [] words;
	delete [] used;
	return 0;
}

// Returns the cost between strings i and j.
int cost(int i, int j) {
	int res = 0;
	for (int z=0; z<k; z++)
		res += abs(words[i][z]-words[j][z]);
	return res;
}
