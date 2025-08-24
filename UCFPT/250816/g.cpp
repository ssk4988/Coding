#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const ll mod = 998244353;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; e /= 2, (b *= b) %= mod)
        if(e&1) (res *= b) %= mod;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int x, y; cin >> x >> y;
        ll a0, a1, b; cin >> a0 >> a1 >> b;
        b = (a0 + a1) % mod;
        b = modpow(b, mod-2);
        (a0 *= b) %= mod;
        (a1 *= b) %= mod;
        ll cur = 1;
        ll ans = 0;
        while(x > 0 && y > 0) {
            if(x == y) {
                (ans += cur * a0) %= mod;
                break;
            }
            int large = max(x, y);
            int small = min(x, y);
            int times = (large - small + small-1) / small;
            ll dontend = modpow(x < y ? a0 : a1, times);
            if(x > y) {
                (ans += (1 - dontend) * cur) %= mod;
            }
            (cur *= dontend) %= mod;
            if(x > y) x -= y * times;
            else y -= x * times;
        }
        (ans += mod) %= mod;
        cout << ans << "\n";
    }

    return 0;
}
