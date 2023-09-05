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

const int LIM = 1e6 + 10;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];
ll MOD = 1e9+7;
 
ll mod(ll k){
    return k % MOD;
}

ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return b;
    ll res = modpow(b, p / 2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i,2,LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](int a, int b) -> ll{
        return mod(fact[a] * mod(invfact[a - b] * invfact[b]));
    };
    ll ans = 0;
    rep(i, 0, k){
        ans = mod(ans + mod1((i % 2 == 0 ? 1 : -1) * choose(k, i) * modpow(k - i, n)));
    }
    cout << ans << nL;
    
    return 0;
}
