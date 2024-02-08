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
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

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
        reverse(all(edges));
        vvi adj(n);
        UF uf(n);
        array<int, 3> best = {1000000000, -1, -1};
        vector<array<int, 3>> cands;
        for(auto [w, u, v] : edges){
            if(uf.join(u, v)) {
                adj[u].pb(v);
                adj[v].pb(u);
            }
            else{
                cands.pb({w, u, v});
            }
        }
        best = cands.back();
        vi ans;
        auto dfs = [&](int u, int p, auto &&dfs) -> bool {
            ans.pb(u);
            if(u == best[2]) return true;
            for(int v : adj[u]){
                if(v == p) continue;
                if(dfs(v, u, dfs)) return true;
            }
            ans.pop_back();
            return false;
        };
        assert(dfs(best[1], -1, dfs));
        cout << best[0] << " " << sz(ans) << "\n";
        for(int i : ans) cout << (i+1) << " ";
        cout << "\n";
    }
    
    return 0;
}
