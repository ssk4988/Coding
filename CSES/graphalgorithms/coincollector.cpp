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

int n, m;
vl k;
vvi cset, adj;
vector<set<int>> radj;
vl cval;
vector<bool> solved;
vi tin, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int u, G& g, F& f) {
	int low = tin[u] = ++Time, x; z.push_back(u);
	for (auto v : g[u]) if (comp[v] < 0)
		low = min(low, tin[v] ?: dfs(v,g,f));

	if (low == tin[u]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != u);
		f(cont); cont.clear();
		ncomps++;
	}
	return tin[u] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	tin.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

void buildcomp(vi v){
    cval.pb(0);
    cset.pb({});
    solved.pb(false);
    radj.pb({});
    for(int i : v){
        cval.back() += k[i];
        cset.back().pb(i);
    }
}

int solve(int cnum){
    if(solved[cnum]) return cval[cnum];


    solved[cnum] = true;
    return cval[cnum];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    k.assign(n, 0);
    adj = vvi(n);
    rep(i, 0, n){
        cin >> k[i];
    }
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
    }
    scc(adj, buildcomp);
    rep(i, 0, n){
        for(int j : adj[i]){
            if(comp[j] == comp[i]) continue;
            radj[comp[i]].insert(comp[j]);
        }
    }
    vl dp(sz(cval));
    vector<bool> vis(sz(cval));
    auto solve = [&](int cur, auto &&solve) -> ll{
        if(vis[cur]) return dp[cur];
        ll path = 0;
        for(int i : radj[cur]){
            path = max(path, solve(i, solve));
        }
        dp[cur] = cval[cur] + path;
        vis[cur] = true;
        return dp[cur];
    };
    // for(int i = sz(cval) - 1; i >= 0; i--){
    //     for(int j : radj[i]){
    //         dp[j] = max(dp[j], cval[i] + dp[i]);
    //     }
    // }
    ll best = 0;
    rep(i, 0, sz(cval)){
        best = max(best, solve(i, solve));//cval[i] + dp[i]);
    }
    cout << best << nL;
    
    return 0;
}
