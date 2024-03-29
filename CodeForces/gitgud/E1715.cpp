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

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vector<vpi> adj(n);
    rep(i, 0, m){
        int a, b, w; cin >> a >> b >> w; a--, b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }
    ll BAD = 1e18;
    vector<vl> dist(k+1, vl(n, BAD));
    dist[0][0] = 0;
    priority_queue<pl, vpl, greater<pl>> pq;
    pq.push({0, 0});
    rep(i, 0, k+1){
        if(i){
            dist[i] = dist[i-1];
            LineContainer lc;
            rep(j, 0, n){
                if(dist[i-1][j] != BAD){
                    lc.add(-(-2 * j), -(ll(j) * j + dist[i-1][j]));
                }
            }
            rep(j, 0, n){
                dist[i][j] = min(dist[i][j], ll(j) * j + -lc.query(j));
                pq.push({dist[i][j], j});
            }
        }
        while(!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if(d > dist[i][u]) continue;
            for(auto [v, w] : adj[u]){
                if(dist[i][v] > d + w){
                    dist[i][v] = d + w;
                    pq.push({dist[i][v], v});
                }
            }
        }
    }
    rep(i, 0, n){
        cout << dist.back()[i] << " ";
    }
    cout << "\n";
    return 0;
}
