#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

const ll LIM = 25'000'100;

const ll MOD = 998244353;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
ll *fact = new ll[LIM] - 1;

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return mod(b);
    ll res = modpow(b, p/2);
    res = mod(res * res);
    if(p % 2 == 1) res = mod(res * b);
    return res;
}
ll modinv(ll k){
    return modpow(k, MOD - 2);
}
ll perm(int n, int k){
    return mod(fact[n] * modinv(fact[n - k]));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = fact[1] = 1;
    rep(i, 2, LIM){
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        ll ans = 0;
        rep(i, 1, n + 1){
            ans = mod(ans + mod(mod(n * n) * mod(perm(n * n - n, i - 1) * fact[n * n - i])));
            // cout << mod(n * n) << " " << perm(n * n - n, i - 1) << " " << fact[n * n - i] << "\n";
        }
        cout << ans << "\n";
    }
}
