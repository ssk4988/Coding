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
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

int getID(int node, bool negated){
    return 2 * node + negated;
}

vi cdx;
void setscc(vi &v){
    for(int i : v){
        cdx[i] = ncomps;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, r, k;
    cin >> n >> r >> k;
    // li being true means vertical
    vpi c(k);
    vvi adj(2 * k);
    rep(i, 0, k){
        cin >> c[i].f >> c[i].s;
    }
    cdx.assign(2 * k, -1);
    rep(i, 0, k){
        rep(j, 0, k){
            if(i == j) continue;
            if(c[i].f == c[j].f && abs(c[i].s - c[j].s) <= 2 * r){
                adj[getID(i, true)].pb(getID(j, false));
            }
            if(c[i].s == c[j].s && abs(c[i].f - c[j].f) <= 2 * r){
                adj[getID(i, false)].pb(getID(j, true));
            }

        }
    }
    scc(adj, setscc);
    bool possible = true;
    rep(i, 0, k){
        if(cdx[getID(i, true)] == cdx[getID(i, false)]){
            possible = false;
        }
    }
    cout << (possible ? 1 : 0) << nL;
    
    return 0;
}