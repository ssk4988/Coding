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

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
    z.clear(); cont.clear();
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vvi adj(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--, b--;
            if(a != b) adj[a].pb(b);
        }
        vi belong(n);
        auto f = [&](vi a){
            for(int i : a){
                belong[i] = ncomps;
            }
        };
        scc(adj, f);
        if(ncomps == 1){
            cout << "No\n";
            continue;
        }
        vi outdeg(ncomps);
        rep(i, 0, n){
            for(int j : adj[i]){
                if(belong[i] != belong[j]) outdeg[belong[i]]++;
            }
        }
        int tar = -1;
        rep(i, 0, ncomps){
            if(outdeg[i] == 0) tar = i;
        }
        assert(tar != -1);
        vi jury, contestants;
        rep(i, 0, n){
            if(belong[i] == tar) jury.pb(i);
            else contestants.pb(i);
        }
        cout << "YES\n";
        cout << sz(jury) << " " << sz(contestants) << nL;
        for(int i : jury) cout << (i + 1) << " ";
        cout << nL;
        for(int i : contestants) cout << (i + 1) << " ";
        cout << nL;
    }
    
    return 0;
}
