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


template <class F, class G> struct centroid {
	G adj;
	F f;
	vi sub_sz, par;
	centroid(const G& adj, F f)
		: adj(adj), f(f), sub_sz(sz(adj), -1), par(sz(adj), -1) {
		rep(i, 0, sz(adj))
			if (sub_sz[i] == -1) dfs(i);
	}
	void calc_sz(int u, int p) {
		sub_sz[u] = 1;
		for (int v : adj[u])
			if (v != p) calc_sz(v, u), sub_sz[u] += sub_sz[v];
	}
	int dfs(int u) {
		calc_sz(u, -1);
		for (int p = -1, sz_root = sub_sz[u];;) {
			auto big_ch = find_if(all(adj[u]), [&](int v) {
				return v != p && 2 * sub_sz[v] > sz_root;
			});
			if (big_ch == end(adj[u])) break;
			p = u, u = *big_ch;
		}
		f(adj, u);
		for (int v : adj[u]) {
			iter_swap(find(all(adj[v]), u), rbegin(adj[v]));
			adj[v].pop_back();
			par[dfs(v)] = u;
		}
		return u;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    ll ans = 0;
    vl freq(n + 1), newfreq(n + 1);
    centroid(adj, [&](const vvi &a, int root) -> void {
        auto dfs = [&](int cur, int par, int d, auto&&dfs)->void {
            if(d <= k)
                ans += freq[k - d];
            newfreq[d]++;
            for(int nex : a[cur]){
                if(nex == par) continue;
                dfs(nex, cur, d+1, dfs);
            }
        };
        freq[0]++;
        for(int nex : a[root]){
            dfs(nex, root, 1, dfs);
            rep(i, 1, sz(newfreq)){
                if(newfreq[i] == 0) break;
                freq[i] += newfreq[i];
                newfreq[i] = 0;
            }
        }
        rep(i, 0, sz(freq)){
            if(freq[i] == 0) break;
            freq[i] = 0;
        }
    });
    cout << ans << "\n";
    
    return 0;
}
