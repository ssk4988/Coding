#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
const ll mod = 1e9+7;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; e /= 2, (b *= b) %= mod) 
        if(e&1) (res *= b) %= mod;
    return res;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, x, y; cin >> n >> x >> y;
    int jumps = 1;
    vl fact(2*n+10), ifact(2*n+10);
    fact[0] = 1;
    rep(i, 1, sz(fact)) {
        fact[i] = fact[i-1] * i % mod;
    }
    ifact.back() = modpow(fact.back(), mod-2);
    for(int i = sz(ifact)-2; i >= 0; i--) {
        ifact[i] = ifact[i+1] * (i+1) % mod;
    }
    auto C = [&](int n, int k) -> ll {
        if(n < 0 || k > n || k < 0) return 0;
        return fact[n] * ifact[k] % mod * ifact[n-k] % mod;
    };
    auto starbar = [&](int alloc, int vars) -> ll {
        return C(alloc + vars-1, vars-1);
    };
    ll ans = 0;
    while(max(x, y) * jumps <= n) {
        (ans += starbar(n-jumps*x, jumps) * starbar(n-jumps*y, jumps)) %= mod;
        jumps++;
    }
    cout << ans << "\n";

    return 0;
}
