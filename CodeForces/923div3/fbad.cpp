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
    // mn(n, 1e9), dep(n), adj(n) 
    
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
        // mn[b] = w;
        // adj[a].pb({b, w});
		e[a] += e[b]; e[b] = a;
		return true;
	}
    // void fix(){
    //     rep(i, 0, sz(e)){
    //         if(e[i] < 0){
    //             dfs(i);
    //         }
    //     }
    // }
    // void dfs(int u){
    //     for(int v : child[u]){
    //         dep[v] = dep[u] + 1;
    //         dfs(v);
    //     }
    // }
    // int mnPath(int u, int v){
    //     int ans = 1e9;
    //     while(u != v){
    //         if(dep[u] >= dep[v]){
    //             ans = min(ans, mn[u]);
    //             u = e[u];
    //         }
    //         else{
    //             ans = min(ans, mn[v]);
    //             v = e[v];
    //         }
    //     }
    //     return ans;
    // }
};

vector<vpi> treeJump(vpi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vpi> jmp(d, P);
	rep(i,1,d) rep(j,0,sz(P))
		jmp[i][j] = {jmp[i-1][jmp[i-1][j].f].f, min(jmp[i-1][jmp[i-1][j].f].s, jmp[i-1][j].s)};
	return jmp;
}

pi jmp(vector<vpi>& tbl, int nod, int steps){
    pi res = {nod, 1e9};
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) {
            res = {tbl[i][res.f].f, min(res.s, tbl[i][res.f].s)};
        }
	return res;
}

int pathMin(vector<vpi>& tbl, vi& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
    int ans = 1e9;
	tie(a, ans) = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return ans;
	for (int i = sz(tbl); i--;) {
		pi c = tbl[i][a], d = tbl[i][b];
		if (c.f != d.f) {
            a = c.f; 
            b = d.f;
            ans = min({ans, c.s, d.s});
        }
	}
    ans = min({ans, tbl[0][a].s, tbl[0][b].s});
	return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<array<int, 3>> edges(m);
        rep(i, 0, m){
            cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
            edges[i][1]--, edges[i][2]--;
        }
        sort(all(edges));
        vector<vpi> adj(n);
        UF uf(n);
        vpi cands;
        for(auto [w, u, v] : edges){
            if(!uf.join(u, v)){
                cands.pb({u, v});
                // best = min(best, {uf.mn[uf.find(u)], u, v});    
            }
            else{
                adj[u].pb({v, w});
                adj[v].pb({u, w});
            }
        }
        vpi par(n, {0, 1e9});
        vi dep(n);
        auto fix = [&](int u, int p, auto &&fix) -> void {
            for(auto [v, w] : adj[u]){
                if(v == p) continue;
                par[v] = {u, w};
                dep[v] = dep[u] + 1;
                fix(v, u, fix);
            }
        };
        rep(i, 0, n){
            if(uf.find(i) == i){
                par[i] = {i, 1e9};
                fix(i, -1, fix);
            }
        }
        vector<vpi> tbl = treeJump(par);
        array<int, 3> best = {1000000000, -1, -1};
        // uf.fix();
        for(auto [u, v] : cands){
            int mn = pathMin(tbl, dep, u, v);
            best = min(best, {mn, u, v});
        }
        vi ans;
        auto dfs = [&](int u, int p, auto &&dfs) -> bool {
            ans.pb(u);
            if(u == best[2]) return true;
            for(auto [v, w] : adj[u]){
                if(v == p) continue;
                if(dfs(v, u, dfs)) return true;
            }
            ans.pop_back();
            return false;
        };
        assert(dfs(best[1], -1, dfs));
        cout << best[0] << " " << sz(ans) << nL;
        for(int i : ans) cout << (i+1) << " ";
        cout << "\n";
    }
    
    return 0;
}
