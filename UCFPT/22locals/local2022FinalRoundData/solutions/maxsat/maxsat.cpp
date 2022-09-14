
#include <bits/stdc++.h>

using namespace std;

// Courtousy of Ben Q
typedef long long int lli;
lli hungarian(const vector<vector<lli>>& a) { 
	int N = a.size()-1, M = a[0].size()-1; assert(N <= M);
	vector<lli> u(N+1), v(M+1); // potentials to make edge weights >= 0
	vector<int> job(M+1);
	for(int i = 1; i < N+1; i++) { // find alternating path with job i
		const lli inf = numeric_limits<lli>::max();
		int w = 0; job[w] = i; // add "dummy" worker 0
		vector<lli> dist(M+1,inf);
        vector<int> pre(M+1,-1);
        vector<bool> done(M+1);
		while (job[w]) { // dijkstra
			done[w] = 1; 
            int j = job[w], nexW; 
            lli delta = inf; 
			// fix dist[j], update dists from j
			for(int W = 0; W < M+1; W++) if (!done[W]) { // try all workers
				if (dist[W] > a[j][W]-u[j]-v[W]){
                    dist[W] = a[j][W]-u[j]-v[W];
                    pre[W] = w;
                }
				if (delta > dist[W]) {
                    delta = dist[W];
                    nexW = W;
                }
			}
			for (int W = 0; W < M+1; W++) { // subtract constant from all edges going 
				// from done -> not done vertices, lowers all 
				// remaining dists by constant
				if (done[W]) u[job[W]] += delta, v[W] -= delta; 
				else dist[W] -= delta; 
			}
			w = nexW;
		} // potentials adjusted so all edge weights >= 0
		for (int W; w; w = W) job[w] = job[W = pre[w]];
	} // job[w] = 0, found alternating path 
	return -v[0]; // min cost
}

int main() {
    int n, s, k;
    cin >> n >> s >> k;
    // Input to hungarian algorithm is 1 indexed so make the array a little bit larger...
    vector<vector<lli>> input(n+1, vector<lli>(n+1));
    for (int i = 1; i <= n; i++) {
        int max = 0;
        int index = 1;
        for (int j = 0; j < s; j++) {
            int amt;
            cin >> amt;
            if (max < amt) max = amt;
            for (int ii = 0; ii < k; ii++)
                input[index++][i] = 1000-(amt);
        }
        // Put them in their best class
        while (index <= n)
            input[index++][i] = 2000-max;
    }
    lli res = hungarian(input);
    cout << -(res-(1000*(2*n-s*k))) << endl;
    return 0;
}
