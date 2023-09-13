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

ll MOD = 1e9 + 7;

ll mod(ll k){
    return k % MOD;
}

ll mod1(ll k){
    while(k >= MOD) k -= MOD;
    return k;
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vl fact(200100), invfact(200100), inv(200100);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i,2,200100){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    vi arr(n);
    int lim = 1 << m;
    vi cnt(lim);
    rep(i, 0, m){
        string str; cin >> str;
        rep(j, 0, n){
            if(str[j] == 'H') arr[j] |= 1 << i;
        }
    }
    rep(i, 0, n){
        cnt[arr[i]]++;
    }
    // auto order = [&](ll x, auto&&order)->ll { return mod(1 + (x == 0 ? 0 : x * order(x - 1, order))); };
    auto order = [&](ll v)->ll{
        ll ans = 0;
        // cout << v << nL;
        rep(i, 0, v + 1){
            ans = mod1(ans + mod(fact[v] * invfact[i]));
        }
        return ans;
    };
    vvl dp(lim, vl(m));
    ll ans = 0;
    rep(i, 0, lim){
        ll sum = 1;
        rep(j, 0, m){
            if(i & (1 << j)){
                sum = mod1(sum + dp[i ^ (1 << j)][j]);
            }
            // sum = mod(sum + dp[i][j]);
        }
        // cout << cnt[i] << nL;
        sum = mod(sum * mod(order(cnt[i]) - 1));
        ans = mod(ans + sum);
        dp[i][0] = sum;
        rep(j, 0, m - 1){
            dp[i][j + 1] = dp[i][j];
            if(i & (1 << j)) dp[i][j + 1] = mod1(dp[i][j + 1] + dp[i ^ (1 << j)][j]);
        }
    }
    cout << ans << nL;



    return 0;
}
