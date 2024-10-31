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

template <class F> struct centroid {
	vector<vi> adj;
	F f;
	vi sub_sz, par;
	centroid(const vector<vi>& a_adj, F a_f)
		: adj(a_adj), f(a_f), sub_sz(sz(adj), -1), par(sz(adj), -1) {
		rep(i, 0, sz(adj))
			if (sub_sz[i] == -1) dfs(i);
	}
	void calc_sz(int u, int p) {
		sub_sz[u] = 1;
		for (int v : adj[u])
			if (v != p)
				calc_sz(v, u), sub_sz[u] += sub_sz[v];
	}
	int dfs(int u) {
		calc_sz(u, -1);
		for (int p = -1, sz_root = sub_sz[u];;) {
			auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) {
				return v != p && 2 * sub_sz[v] > sz_root;
			});
			if (big_ch == end(adj[u])) break;
			p = u, u = *big_ch;
		}
		f(adj, u);
		for (int v : adj[u]) {
			iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
			adj[v].pop_back();
			par[dfs(v)] = u;
		}
		return u;
	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret, depth;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), depth(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			depth[y] = depth[v] + 1;
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a, int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n, k;
	cin >> n >> k;
	vvi adj(n);
	rep(i, 0, n-1){
		int u, v; cin >> u >> v; u--, v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	vvi centroids(n);
	LCA lca(adj);
	centroid cc(adj, [](auto &v, auto c) {});
	vi ord(n);
	iota(all(ord), 0);
	sort(all(ord), [&](int a, int b) -> bool {
		return lca.depth[a] > lca.depth[b];
	});
	vi ans;
	vi closest(n, k+10);
	for(int i : ord){
		int c = 1e9;
		for(int u = i; u != -1; u = cc.par[u])
			c = min(lca.dist(i, u) + closest[u], c);
		if(c < k) continue;
		ans.pb(i);
		for(int u = i; u != -1; u = cc.par[u])
			closest[u] = min(closest[u], lca.dist(i, u));
	}
	cout << sz(ans) << "\n";
	for(int i : ans){
		cout << i+1 << " ";
	}
	cout << "\n";
	
	
	return 0;
}
