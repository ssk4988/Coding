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

const int LIM = 4e6 + 100;
ll fact[LIM], invfact[LIM], inv[LIM];

ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll ans = 1;
    int n; cin >> n;
    fact[0] = fact[1] = invfact[0] = invfact[1] = 1;
    inv[1] = 1;
    for(int i = 2; i < LIM; ++i){
        inv[i] = MOD - (MOD/i) * inv[MOD%i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](ll n, ll k)->ll{
        return mod(fact[n] * mod(invfact[n - k] * invfact[k]));
    };
    ll pre = -1;
    rep(i, 0, n){
        ll v; cin >> v;
        v /= 2;
        if(i){
            if(v >= pre){
                ans = mod(ans * choose(v - 1, pre - 1));
            }
            else{
                ans = mod(ans * choose(pre, v));
            }
        }
        pre = v;
    }
    cout << ans << "\n";
    
    return 0;
}