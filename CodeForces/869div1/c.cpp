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

const int LIM = 25e5 + 100;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];
ll MOD = 1e9 + 7;

ll mod(ll k)
{
    return (k % MOD + MOD) % MOD;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return b;
    ll res = modpow(b, p/2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}

ll modinv(ll a){
    return modpow(a, MOD - 2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i, 2, LIM)
    {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](int a, int b) -> ll
    {
        return mod(fact[a] * mod(invfact[a - b] * invfact[b]));
    };
    auto dd = [&](vl &arr, int x, int d) -> ll
    {
        ll ans = 0;
        rep(i, 0, d + 1)
        {
            ll sig = i % 2 == 0 ? 1 : -1;
            ans = mod(ans + mod(sig * choose(d, i) * arr[x + i]));
        }
        return ans;
    };
    int d;
    cin >> d;
    vl a(d + 1), b(d + 1);
    rep(i, 0, d + 1)
    {
        cin >> a[i];
    }
    rep(i, 0, d + 1)
    {
        cin >> b[i];
    }
    ll a0 = dd(a, 0, d - 1), a1 = dd(a, 1, d - 1), b0 = dd(b, 0, d - 1), b1 = dd(b, 1, d - 1);
    ll as = mod(a1 - a0), bs = mod(b1 - b0);
    assert(as == bs);
    ll res = mod(b1 - a1);
    res = mod(modinv(as) * res);
    cout << res << nL;

    return 0;
}
