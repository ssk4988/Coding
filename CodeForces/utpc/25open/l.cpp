#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

const ll mod = 1e9+7;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; b=(b*b)%mod, e /= 2){
        if(e&1) (res *= b) %= mod;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n; cin >> n;
    vl divs;
    for(ll d = 1; d*d <= n; d++) {
        if(n % d == 0) {
            divs.push_back(d);
            if(d != n/d) divs.push_back(n/d);
        }
    }
    sort(all(divs));
    vl inc(sz(divs));
    ll ans = 0;
    for(int i = sz(divs)-1; i >= 0; i--) {
        ll cnt = n / divs[i];
        cnt %= mod;
        inc[i] = divs[i] % mod * cnt % mod * (cnt+1) % mod * modpow(2, mod-2) % mod;
        rep(j, i+1, sz(divs)) {
            if(divs[j] % divs[i] != 0) continue;
            (inc[i] -= inc[j]) %= mod;
        }
        (ans += inc[i] * modpow(divs[i] % mod, mod-2)) %= mod;
    }
    (ans += mod) %= mod;
    (ans *= n % mod) %= mod;
    cout << ans << "\n";

    return 0;
}
