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
const ll mod = 1e9+7;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    n *= 2;
    vi a(n, -1);
    vvi child(n);
    vi seen(n);
    rep(i, 0, n/2) {
        int u, v; cin >> u >> v; u--, v--;
        a[u] = v;
        child[v].push_back(u);
    }
    vi roots;
    ll ans = 1;
    rep(i, 0, n) {
        if(seen[i]) continue;
        int u = i;
        vi path;
        while(u != -1 && !seen[u]) {
            path.push_back(u);
            seen[u] = 1;
            u = a[u];
        }
        if(u == -1) {
            roots.push_back(path.back());
        } else {
            int p = sz(path)-1;
            while(p >= 0 && path[p] != u) p--;
            if(p < 0) continue;
            int cycsize = sz(path) - p;
            if(cycsize > 1) (ans *= 2) %= mod;
        }
    }

    vector<array<ll, 2>> dp(n, array<ll, 2>{-1, -1});
    auto go = [&](int u, auto &&go) -> array<ll, 2> {
        auto &ans = dp[u];
        if(ans[0] != -1) return ans;
        ans[0] = 1;
        ans[1] = 1;
        for(int v : child[u]) {
            auto c = go(v, go);
            array<ll, 2> nxt{ans[0] * c[0] % mod, ans[1] * c[0] + ans[0] * c[1]};
            nxt[1] %= mod;
            ans = nxt;
        }
        return ans;
    };
    for(int r : roots) {
        auto cur = go(r, go);
        (ans *= cur[1]) %= mod;
    }
    cout << ans << "\n";
    // rep(i, 0, n) {
    //     cerr << i << " " << go(i, go)[0] << " " << go(i, go)[1] << endl;
    // }

    
    
    return 0;
}
