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
struct Line
{
    mutable ll k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>>
{
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b)
    { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y)
    {
        if (y == end())
            return x->p = inf, 0;
        if (x->k == y->k)
            x->p = x->m > y->m ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m)
    {
        m *= -1;
        k *= -1;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x)
    {
        assert(!empty());
        auto l = *lower_bound(x);
        return -(l.k) * x + (-l.m);
    }
};

const int MAXN = 200'005;
bool removed[MAXN];  // removed
int subsz[MAXN];   // subtree size
vvi adj(MAXN);
vector<vector<pair<int, ll>>> wadj(MAXN);
vl cost(MAXN);
vl best(MAXN, LLONG_MAX);
int dfs(int n, int p = 0) {
	subsz[n] = 1;
	for (int x : adj[n])
		if (x != p && !removed[x]) subsz[n] += dfs(x, n);
	return subsz[n];
}
int get_centroid(int n, int ms,
                 int p = 0)  // n = node, ms = size of tree, p = parent
{
	for (int x : adj[n])
		if (x != p && !removed[x])
			if (subsz[x] * 2 > ms) return get_centroid(x, ms, n);
	return n;
}

void lcdfs(int n, int p, ll dist, LineContainer &lc){
    lc.add(cost[n], dist);
    for(pair<int, ll> &P : wadj[n]){
        auto [x, d] = P;
        if(x != p && !removed[x]){
            lcdfs(x, n, dist + d, lc);
        }
    }
}

void chdfs(int n, int p, ll dist, LineContainer &lc){
    best[n] = min(best[n], dist + lc.query(cost[n]));
    for(pair<int, ll> &P : wadj[n]){
        auto [x, d] = P;
        if(x != p && !removed[x]){
            chdfs(x, n, dist + d, lc);
        }
    }
}

void centroid(int n = 1) {
	int C = get_centroid(n, dfs(n));

	// do something
    LineContainer lc;
    lcdfs(C, 0, 0, lc);
    chdfs(C, 0, 0, lc);

	removed[C] = 1;
	for (int x : adj[C])
		if (!removed[x]) centroid(x);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    rep(i, 0, n){
        cin >> cost[i+1];
    }
    rep(i, 0, n - 1){
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].pb(b);
        adj[b].pb(a);
        wadj[a].pb({b, w});
        wadj[b].pb({a, w});
    }
    centroid();
    ll ans = 0;
    rep(i, 1, n + 1){
        assert(best[i] != LLONG_MAX);
        ans += best[i];
    }
    cout << ans << nL;
    
    return 0;
}
