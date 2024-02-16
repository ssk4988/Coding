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

const ll mod = 998244353; // change to something else
ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}
// struct Mod {
// 	ll x;
// 	Mod(ll xx=0) : x(xx) {}
// 	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
// 	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
// 	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
// 	Mod operator/(Mod b) { return *this * invert(b); }
// 	Mod invert(Mod a) {
// 		ll x, y, g = euclid(a.x, mod, x, y);
// 		assert(g == 1); return Mod((x + mod) % mod);
// 	}
// 	Mod operator^(ll e) {
// 		if (!e) return Mod(1);
// 		Mod r = *this ^ (e / 2); r = r * r;
// 		return e&1 ? *this * r : r;
// 	}
// };
using Mod = double;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, Mod>>> adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        int p, q; cin >> p >> q;
        a--, b--;
        adj[a].push_back({b, Mod(p) / Mod(q)});
    }
    vi vis(n);
    vector<Mod> aware(n);
    aware[0] = 1;
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(vis[u]) return;
        vis[u] = true;
        for(auto [v, w] : adj[u]){
            aware[v] = aware[v] + w * aware[u] * (aware[v] * -1 + 1);
            dfs(v, dfs);
        }
    };
    dfs(0, dfs);
    rep(i, 0, n){
        cout << aware[i] << "\n";
        // cout << aware[i].x << "\n";
    }
    return 0;
}