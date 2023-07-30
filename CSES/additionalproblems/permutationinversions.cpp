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


const int maxk = 500 * 499 / 2 + 5;
ll dp[501][maxk];

const ll MOD = 1e9 + 7;
ll mod(ll k){
    k %= MOD;
    if(k < 0) k = (k + MOD) % MOD;
    return k;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    dp[0][0] = 1;
    dp[0][1] = -1;
    int n, k; cin >> n >> k;
    rep(i, 0, n){
        ll pref = 0;
        rep(j, 0, maxk){
            pref = mod(pref + dp[i][j]);
            if(pref == 0) continue;
            // cout << "dp[" << i << "][" << j << "]=" << pref << nL;
            dp[i + 1][j] = mod(dp[i + 1][j] + pref);
            if(j + i + 1 + 1 < maxk) dp[i + 1][j + i + 1 + 1] = mod(dp[i + 1][j + i + 1 + 1] - pref);
        }
    }
    ll pref = 0;
    rep(j, 0, k + 1){
        pref = mod(pref + dp[n - 1][j]);
    }
    cout << pref << nL;
    
    return 0;
}