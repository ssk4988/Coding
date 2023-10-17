#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}
ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}
struct ModChoose {
    // const ll MOD;
    const int LIM;
    vl inv, fact, invfact;
    ModChoose(int n) : LIM(n + 1), inv(LIM), fact(LIM), invfact(LIM) {
        fact[0] = invfact[0] = inv[1] = fact[1] = invfact[1] = 1;
        rep(i, 2, LIM){
            inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
            fact[i] = (i * fact[i - 1]) % MOD;
            invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
        }
    }
    ll choose(int n, int k){
        if(k > n || k < 0) return 0;
        return (fact[n] * invfact[k]) % MOD * invfact[n - k] % MOD;
    }
    ll starsbars(int numalloc, int numvars){
        return choose(numalloc + numvars - 1, numvars - 1);
    }
};

int main(){
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, h; cin >> n >> h;
    ModChoose c(2 * n + 100);
    if(h == 0){
        cout << c.fact[n] << "\n";
        return 0;
    }
    vi freq(h);
    rep(i, 0, h){
        cin >> freq[i];
    }
    // sort(all(freq));
    // reverse(all(freq));
    vi pref(freq);
    rep(i, 1, h){
        pref[i] += pref[i - 1];
    }
    // if(n - pref.back() == 0){
    //     cout << 0 << "\n";
    //     return 0;
    // }
    vl dp(h);
    dp[0] = c.fact[freq[0]];
    // cout << "calcd prefs\n";
    rep(i, 1, h){
        ll v = 0;
        int f = freq[i];
        rep(j, 0, i){
            // dp[i] = mod(dp[i] + )
            int b = pref[j];
            int u = pref[i - 1] - pref[j];
            // ll interleaves = 0;
            // rep(k, 0, b){
            //     interleaves = mod(interleaves + c.starsbars(f - 1, b - k + u + 1));
            // }
            ll fastinterleaves = mod1(c.choose(f + b + u, f) - c.choose(f + u, f));
            ll cont = mod(c.fact[u] * mod(dp[j] * fastinterleaves));
            // cout << "houses " << i << " from " << j << " contributes " << cont << "\n";
            v = mod(v + cont);
        }
        v = mod(v * c.fact[f]);
        dp[i] = v;
        // cout << i << " " << dp[i] << "\n";
        // cout << "calcd " << i << "\n";
    }
    ll ans = c.fact[n];
    rep(i, 0, h){
        ans = mod1(ans - mod(c.fact[n - pref[i]] * dp[i]));
    }
    cout << ans << "\n";


    return 0;
}
