#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct UF {
	vi e;
    vvi es;
	UF(int n) : e(n, -1), es(n) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b, int i) {
		a = find(a), b = find(b);
		if (a == b) { es[a].pb(i); return false;}
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        for(int x : es[b]) es[a].pb(x);
        es[b].clear();
        es[a].pb(i);
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vii e(q);
    vector<vector<pair<int, vi>>> adj(n);
    vi deg(n);

    vector<array<int, 3>> es;
    rep(i, 0,q){
        cin >> e[i].f >> e[i].s; e[i].f--, e[i].s--;
        // adj[e[i].f].pb({e[i].s, i});
        // adj[e[i].s].pb({e[i].f, i});
        deg[e[i].f]++;
        deg[e[i].s]++;
        es.push_back({min(e[i].f, e[i].s), max(e[i].f, e[i].s), i});
    }
    sort(all(es));
    rep(i, 0, sz(es)) {
        if(i == 0 || !(es[i][0] == es[i-1][0] && es[i][1] == es[i-1][1])){
            adj[es[i][0]].pb({es[i][1], {es[i][2]}});
            adj[es[i][1]].pb({es[i][0], {es[i][2]}});
        } else{
            adj[es[i][0]].back().s.pb(es[i][2]);
            adj[es[i][1]].back().s.pb(es[i][2]);
        }
    }
    vi l(q), d(q);
    vi par(n);
    vi seen(n);
    vi used(q);
    int T = 0;
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        seen[u] = ++T;
        for(auto [v, ids] : adj[u]) {
            if(seen[v]) {
                for(int id : ids) {
                    if(used[id]) continue;
                    used[id] = true;
                    par[v] ^= 1;
                    l[id] = e[id].s == v;
                }
            } else {
                vi todo;
                for(int id : ids) {
                    if(used[id]) continue;
                    todo.pb(id);
                    used[id] = true;
                }
                dfs(v, u, dfs);
                for(int id : todo) {
                    if(par[v]) {
                        par[v] ^= 1;
                        l[id] = e[id].s == v;
                    } else {
                        par[u] ^= 1;
                        l[id] = e[id].s == u;
                    }
                }
            }
        }
    };
    rep(i, 0, n) {
        if(!seen[i]) dfs(i, -1, dfs);
    }
    par = vi(n);
    rep(i, 0, q) {
        auto [x, y] = e[i];
        if(par[l[i] ? y : x]) d[i] = -1;
        else d[i] = 1;
        par[l[i] ? y : x] ^= 1;
        cout << (l[i] ? 'y' : 'x') << (d[i] == 1 ? '+' : '-') << "\n";
    }
    
    return 0;
}
