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

const ll MOD = 1e9 + 7;
inline ll mod(ll k) {
    return k % MOD;
}
inline ll mod1(ll k) {
    return (k + MOD) % MOD;
}

vl inv, fact, invfact;
const int LIM = 1e6 + 10;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    inv.resize(LIM), fact.resize(LIM), invfact.resize(LIM);
    fact[0] = invfact[0] = inv[1] = fact[1] = invfact[1] = 1;
    rep(i, 2, LIM) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = (i * fact[i - 1]) % MOD;
        invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
    }
    int n, k; cin >> n >> k;
    vl d(n+1), pref(n+2);
    rep(i, k+1, n+1) {
        d[i] = mod(mod((i - k - 1) * fact[i-2]) + mod(fact[i-2] * mod1(pref[i] - pref[i - k])));
        pref[i+1] = mod(pref[i] + mod(d[i] * invfact[i-1]));
    }
    ll ans = 0;
    rep(i, 1, n+1){
        ans = mod(ans + mod(d[i] * mod(fact[n-1] * invfact[i-1])));
    }
    cout << ans << "\n";
    
    return 0;
}
