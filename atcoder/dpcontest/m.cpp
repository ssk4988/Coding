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

using T = pair<ll, int>;
const ll mod = 998244353;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; (b *= b) %= mod, e /= 2)
        if(e&1) (res *= b) %= mod;
    return res;
}
T op(T a, T b) {
    return {(a.first * modpow(10, b.second) + b.first) % mod, a.second + b.second};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string s; cin >> s;
    vi a(sz(s));
    rep(i, 0, sz(s)) a[i] = s[i] - '0';
    vector<T> cat(sz(s));
    rep(i, 0, sz(s)) {
        cat[i] = T{a[i], 1};
    }
    rep(b, 0, n) {
        rep(mask, 0, 1 << n) {
            if((mask >> b)&1) {
                cat[mask] = op(cat[mask ^ (1 << b)], cat[mask]);
            }
        }
    }
    ll ans = 0;
    rep(mask, 0, 1 << n) {
        ans += cat[mask].first ^ mask;
        // cerr << mask << " " << cat[mask].first << " " << cat[mask].second << endl;
    }
    cout << ans << "\n";
    
    
    return 0;
}
