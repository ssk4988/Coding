#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll mod = 1e9+7;

ll modpow(ll b, ll p) {
    ll res = 1;
    for(; p; (b *= b) %= mod, p /= 2) {
        if(p & 1) (res *= b) %= mod;
    }
    return res;
}

vl integrate(vl p) {
    vl q(sz(p) + 1);
    rep(i, 1, sz(q)) {
        q[i] = modpow(i, mod-2) * p[i-1] % mod;
    }
    return q;
}

vl conv(vl a, vl b) {
    vl res(sz(a) + sz(b) - 1);
    rep(i, 0, sz(a)) {
        rep(j, 0, sz(b)) {
            (res[i+j] += a[i] * b[j]) %= mod;
        }
    }
    return res;
}

ll eval(vl &p, ll x) {
    ll ans = 0;
    ll b = 1;
    rep(i, 0, sz(p)) {
        (ans += p[i] * b) %= mod;
        (b *= x) %= mod;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi child(n);
    int root = -1;
    vl b(n);
    rep(i, 0, n) {
        cin >> b[i];
        int p; cin >> p; p--;
        if(p < 0) {
            root = i;
        } else child[p].pb(i);
    }
    auto dfs = [&](int u, auto &&dfs) -> vl {
        vl res{modpow(b[u], mod-2)};

        for(int v : child[u]) {
            vl w = integrate(dfs(v, dfs));
            ll tot = eval(w, b[v]);
            rep(i, 0, sz(w)) {
                w[i] = (mod - w[i]) % mod;
            }
            (w[0] += tot) %= mod;
            res = conv(res, w);
            b[u] = min(b[u], b[v]);
        }
        return res;
    };
    vl p = dfs(root, dfs);
    p = integrate(p);
    ll ans = eval(p, b[root]);
    cout << ans << "\n";
    
    return 0;
}
