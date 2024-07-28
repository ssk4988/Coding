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

vi eulerWalk(vector<vector<pi>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	// D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vi score(n);
        vvi adj(n);
        vpi edges; // used in euler tour
        rep(_, 0, m){
            int u, v, c; cin >> u >> v >> c; u--, v--;
            if(c){
                score[u] ^= 1;
                score[v] ^= 1;
                edges.pb({u, v});
            } else {
                adj[u].pb(v);
                adj[v].pb(u);
            }
        }
        vi seen(n);
        // vi cnt(n);
        // vi par(n, -1);
        auto dfs = [&](int u, auto &&dfs) -> int {
            if(seen[u]) return 0;
            seen[u] = 1;
            int res = score[u];
            for(int v : adj[u]){
                if(seen[v]) continue;
                // par[v] = u;
                int c = dfs(v, dfs);
                if(c){
                    edges.pb({u, v});
                }
                res ^= c;
            }
            return res;
        };
        bool works = true;
        rep(i, 0, n){
            if(dfs(i, dfs)) works = false;
        }
        if(!works) {
            cout << "NO\n";
            continue;
        }
        vector<vpi> g(n);
        rep(i, 0, sz(edges)){
            auto [u, v] = edges[i];
            g[u].pb({v, i});
            g[v].pb({u, i});
        }
        vi res = eulerWalk(g, sz(edges));
        assert(sz(res) > 0);
        cout << "YES\n";
        cout << sz(edges) << "\n";
        for(int i : res){
            cout << i+1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
