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
using vvl = vector<vl>;

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

ll LIM = 5e5 + 10;
vl inv(LIM, 1), fact(LIM, 1), invfact(LIM, 1);

ll MOD = 998244353;
ll mod(ll k)
{
    return (k % MOD + MOD) % MOD;
}

ll choose(int n, int k){
    if(k < 0 || k > n) return 0;
    return mod(mod(fact[n] * invfact[k]) * invfact[n - k]);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i, 2, LIM)
    {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(fact[i - 1] * i);
        invfact[i] = mod(invfact[i - 1] * inv[i]);
    }
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    rep(i, 1, n + 1){
        ans = mod(ans + choose(n / i - 1, k - 1));
    }
    cout << ans << nL;
    return 0;
}
