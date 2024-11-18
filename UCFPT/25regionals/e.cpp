#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	int n, q; cin >> n >> q;
	vi furthest(n), comp(n), diam;
	vvi adj(n);
	rep(i, 0, n-3){
		int u, v; cin >> u >> v; u--, v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	rep(i, 0, n){
		if(furthest[i]) continue;
		auto dfs = [&](int u, int p, int d, auto &&dfs) -> pii {
			pii res{0, u};
			comp[u] = size(diam);
			furthest[u] = max(furthest[u], d);
			for(int v : adj[u]) if(v != p) {
				pii a = dfs(v, u, 1+d, dfs);
				a.f += 1;
				res = max(res, a);
			}
			return res;
		};
		pii a = dfs(i, -1, 0, dfs);
		pii b = dfs(a.s, -1, 0, dfs);
		pii c = dfs(b.s, -1, 0, dfs);
		diam.pb(c.f);
	}
	rep(i, 0, q){
		int u, v; cin >> u >> v; u--, v--;
		cout << furthest[u] + furthest[v] + 3 + diam[3 - comp[u] - comp[v]] << "\n";
	}
}
