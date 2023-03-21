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


vector<bool> removed;  // removed
vi subsz, cost;   // subtree size
vvi adj;
ll ans = 0;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int dfs(int n, int p = -1) {
	subsz[n] = 1;
	for (int x : adj[n])
		if (x != p && !removed[x]) subsz[n] += dfs(x, n);
	return subsz[n];
}
int get_centroid(int n, int ms,
                 int p = -1)  // n = node, ms = size of tree, p = parent
{
	for (int x : adj[n])
		if (x != p && !removed[x])
			if (subsz[x] * 2 > ms) return get_centroid(x, ms, n);
	return n;
}

void lcdfs(int n, int p, int pathMax, ll dist, int nodeDist, vector<pair<ll, int>> &stuff){
    if(nodeDist > 0) stuff.pb({dist, pathMax});
    for(int x : adj[n]){
        if(x != p && !removed[x]){
            lcdfs(x, n, max(cost[x], pathMax), dist + cost[x], nodeDist + 1, stuff);
        }
    }
}

void centroid(int n = 0) {
	int C = get_centroid(n, dfs(n));

	// do something
    vector<pair<ll, int>> stuff;
    lcdfs(C, -1, cost[C], cost[C], 0, stuff);
    sort(all(stuff));
	set<ll> keys;
	rep(i, 0, sz(stuff)){
		keys.insert(stuff[i].f);
		keys.insert(2LL * stuff[i].s + cost[C] - stuff[i].f);
		keys.insert(2LL * stuff[i].s + cost[C] - stuff[i].f + 1);
	}
	map<ll, int> cc;
	int val = 1;
	for(ll key : keys){
		cc[key] = val++;
	}
	FT ft(val);
	rep(i, 0, sz(stuff)){
		ans += ft.query(val) - ft.query(cc[1LL + 2 * stuff[i].s + cost[C] - stuff[i].f]);
		ft.update(cc[stuff[i].f], 1);
	}

	removed[C] = 1;
	for (int x : adj[C])
		if (!removed[x]) centroid(x);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        subsz.assign(n, 0);
        cost.assign(n, 0);
        adj.assign(n, {});
        removed.assign(n, false);
        ans = 0;
        rep(i, 0,n ){
            cin >> cost[i];
        }
        rep(i, 0, n-1){
            int a, b; cin >> a >> b;
            a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
		centroid(0);
		cout << ans << nL;
    }
    
    return 0;
}
