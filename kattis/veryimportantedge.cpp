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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		// if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edges(m);
    rep(i, 0, m){
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0]; edges[i][1]--, edges[i][2]--;
    }
    vi edgeorder(m), unused, depth(n), par(n, -1), orig(n), best(n);
    iota(all(edgeorder), 0);
    sort(all(edgeorder), [&](int u, int v) -> bool { return edges[u] < edges[v]; });
    UF uf(n), path(n);
    vvi adj(n);
    ll sum = 0;
    rep(i, 0, m){
        if(!uf.join(edges[edgeorder[i]][1], edges[edgeorder[i]][2])){
            unused.pb(edgeorder[i]);
        }
        else {
            adj[edges[edgeorder[i]][1]].pb(edgeorder[i]);
            adj[edges[edgeorder[i]][2]].pb(edgeorder[i]);
            sum += edges[edgeorder[i]][0];
        }
    }
    auto other = [&](int u, int e) -> int { return edges[e][1 + (edges[e][1] == u)]; };
    auto dfs = [&](int u, int e, auto &&dfs) -> void {
        if(e != -1) {
            par[u] = other(u, e);
            orig[u] = edges[e][0];
        }
        for(int e1 : adj[u]){
            if(e1 == e) continue;
            int v = other(u, e1);
            depth[v] = depth[u] + 1;
            dfs(v, e1, dfs);
        }
    };
    dfs(0, -1, dfs);
    for(int e : unused) {
        auto [w, u, v] = edges[e];
        u = path.find(u), v = path.find(v);
        while(u != v) {
            int upd = depth[u] >= depth[v] ? u : v;
            best[upd] = w, path.join(par[upd], upd);
            u = path.find(u), v = path.find(v);
        }
    }
    int mx = 0;
    rep(i, 0, n) mx = max(mx, best[i] - orig[i]);
    cout << (mx + sum) << "\n";
    
    return 0;
}
