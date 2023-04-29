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

ll MOD = 998244353;

ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
ll modmul(ll a, ll b, ll M) {
    ll ret = a * b - M * ll(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll) M);
}

ll modpow(ll b, ll e, ll mod){
    ll ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2){
        if(e & 1) ans = modmul(ans, b, mod);
    }
    return ans;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, v; cin >> n >> v;
    ll m = n - v;
    if(m < 0 || m > n){
        cout << "0\n";
        return 0;
    }
    int LIM = 200'010;
    vl fact(LIM), invfact(LIM), inv(LIM);
    fact[0] = invfact[0] = inv[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    
    rep(i, 2, LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(fact[i - 1] * i);
        invfact[i] = mod(invfact[i - 1] * inv[i]);
        // assert(mod(fact[i] * invfact[i]) == 1);
    }
    if(v == 0){
        cout << fact[n] << nL;
        return 0;
    }
    auto choose = [&](int n, int k)->ll{
        if(k < 0 || k > n) return 0;
        return mod(mod(fact[n] * invfact[n - k]) * invfact[k]);
    };

    ll ans = 0;
    rep(i, 0, m + 1){
        int sig = (i % 2 == 0) ?    1 : -1;
        ans = mod(ans + mod(sig * choose(m, i) * modpow(m - i, n, MOD)));
    }
    ans = mod(ans * invfact[m]);
    ans = mod(ans * mod(fact[n] * invfact[n - m]));
    cout << mod(2 * ans) << nL;


    
    return 0;
}