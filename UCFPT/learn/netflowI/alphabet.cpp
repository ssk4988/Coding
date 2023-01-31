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
        vector<unordered_map<int, int>> graph(54);
        string st1, st2; cin >> st1 >> st2;
        rep(i, 0, st1.length()){
            graph[0][st1[i] + 1 - 'a']++;
        }
        rep(i, 0, st2.length()){
            graph[26 + 1 + st2[i] - 'a'][53]++;
        }
        rep(i, 1, 27){
            rep(j, 27 ,53){
                if(abs((i + 26) - j) >= 3){
                    graph[i][j] = 5000;
                }
            }
        }
        int mf = edmondsKarp(graph, 0, 53);
        cout << mf << nL;
    }
    
    
    return 0;
}
