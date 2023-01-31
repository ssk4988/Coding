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
    int n; cin >> n;
    vector<unordered_map<int, ll>> residual(n + 2), graph(n + 2);
    vi a(n), b(n);
    ll inf = 1e9;
    ll net = 0;
    rep(i, 0, n){
        cin >> a[i] >> b[i];
        // residual[0][i + 1] = a[i];
        // residual[i + 1][n + 1] = b[i];
        // net += a[i] + b[i];
        if(a[i] > b[i]){
            residual[0][i + 1] = a[i] - b[i];
            net += a[i] - b[i];
        }
        else if(b[i] > a[i]){
            residual[i + 1][n + 1] = b[i] - a[i];
        }
        int m; cin >> m;
        rep(j, 0, m){
            int k; cin >> k;
            residual[k][i + 1] = inf;
            residual[i + 1][k] = 0;
        }
    }
    rep(i, 0, n + 2){
        graph[i] = residual[i];
    }
    ll flow = edmondsKarp(residual, 0, n + 1);
    cout << net - flow << nL;


    
    return 0;
}
