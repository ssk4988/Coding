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

ll MOD = 1e9 +7;

ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int v; cin >> v;
    int r, c, n;
    r = c = v;
    cin >> n;
    vpi block(n);
    rep(i, 0, n){
        cin >> block[i].f >> block[i].s;
    }
    int LIM = 2'000'010;
    vl fact(LIM), invfact(LIM), inv(LIM);
    fact[0] = invfact[0] = inv[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    
    rep(i, 2, LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(fact[i - 1] * i);
        invfact[i] = mod(invfact[i - 1] * inv[i]);
        // assert(mod(fact[i] * invfact[i]) == 1);
    }
    auto choose = [&](int n, int k)->ll{
        return mod(mod(fact[n] * invfact[n - k]) * invfact[k]);
    };
    block.pb({1, 1});
    block.pb({r, c});
    sort(all(block));
    vl dp(sz(block));
    // check upper left and bottom right blocked
    dp[0] = mod(-1);
    rep(i, 0, sz(dp)){
        rep(j, i + 1, sz(dp)){
            if(block[j].f >= block[i].f && block[j].s >= block[i].s){
                int dx = block[j].f - block[i].f, dy = block[j].s - block[i].s;
                ll val = choose(dx + dy, dx);
                dp[j] = mod(dp[j] - mod(dp[i] * val));
            }
        }
    }
    cout << dp.back() << nL;
    return 0;
}