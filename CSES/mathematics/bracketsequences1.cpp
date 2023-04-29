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

const int LIM = 2e6 + 10;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];
ll MOD = 1e9+7;

ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
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
    int n; cin >> n;

    if(n % 2 == 1) cout << 0 << nL;
    else{
        n/=2;
        cout << mod(fact[2*n] * mod(mod(invfact[n] * invfact[n]) * inv[n + 1])) << nL;
    }
    
    return 0;
}