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

const int LIM = 1e3 + 10;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];

ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
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
    string str; cin >> str;
    int n= sz(str);
    vector<vl> dp(n + 1, vl(n));
    rep(i, 0, n){
        dp[i + 1][i] = 1;
    }
    for(int len = 2; len <= n; len++){
        for(int l = 0; l + len <= n; l++){
            int r = l + len - 1;
            if(len == 2){
                dp[l][r] = str[l] == str[r];
                continue;
            }
            for(int len1 = 2; len1 < len; len1 += 2){
                if(str[l] == str[l + len1 - 1]) dp[l][r] = mod(dp[l][r] + mod(mod(choose(len / 2, len1 / 2) * dp[l + 1][l + len1 - 2]) * dp[l + len1][r]));
            }
            if(str[l] == str[r]){
                dp[l][r] = mod(dp[l][r] + dp[l + 1][r - 1]);
            }
        }
    }
    // rep(i, 0, n){
    //     rep(j, 0, n){
    //         if(dp[i][j]) cout << i << " " << j << " " << dp[i][j] << "\n";
    //     }
    // }
    cout << dp[0][n - 1] << "\n";
    
    return 0;
}