#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

template<class T> T edmondsKarp(vector<unordered_map<int, T>>& graph, int source, int sink) {
	assert(source != sink);
	T flow = 0;
	vi par(sz(graph)), q = par;

	for (;;) {
		fill(all(par), -1);
		par[source] = 0;
		int ptr = 1;
		q[0] = source;

		rep(i,0,ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) goto out;
				}
			}
		}
		return flow;
out:
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi horiz, vert;
        vector<unordered_map<int, int>> graph(n + 2);
        vector<bool> inCut(n + 2), connected(n + 2);
        rep(i, 0, n){
            vi c(4);
            rep(j, 0, 4) cin >> c[j];
            if(c[0] > c[2] || c[1] > c[3]){
                swap(c[0], c[2]);
                swap(c[1], c[3]);
            }
            if(c[0] == c[2]){
                vert.pb(c);
            }
            else{
                horiz.pb(c);
            }
        }
        int ints = 0;
        rep(i, 0, horiz.size()){
            rep(j, 0, vert.size()){
                if(vert[j][1] <= horiz[i][1] && horiz[i][1] <= vert[j][3] && horiz[i][0] <= vert[j][0] && vert[j][0] <= horiz[i][2]){
                    graph[i + 1][horiz.size() + 1 + j] = 1000000;
                    connected[i + 1] = true;
                    connected[horiz.size() + 1 + j] = true;
                    ints++;
                }
            }
        }
        rep(i, 0, horiz.size()){
            graph[0][i + 1] = 1;
        }
        rep(i, 0, vert.size()){
            graph[horiz.size() + 1 + i][n + 1] = 1;
        }
        int mf = edmondsKarp(graph, 0, n + 1);
        
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int k = q.front();  q.pop();
            if(inCut[k]) continue;
            inCut[k] = true;
            for(auto &e : graph[k]){
                if(e.s == 0) continue;
                if(!inCut[e.f]) q.push(e.f);
            }
        }
        int minnodecover = 0;
        rep(i, 1, horiz.size() + vert.size() + 1){
            if(connected[i] && inCut[i] == (i > horiz.size())){
                minnodecover++;
            }
        }
        // rep(i, horiz.size() + 1, n + 1){
        //     if(inCut[i]) minnodecover++;
        // }
        cout << (n - mf) << nL;
        // cout << ints << nL;
    }
    
    return 0;
}
