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
ll MOD = 1e9 + 7;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    if(((n + 1) * n / 2) % 2 == 1) {cout << 0 << nL;return 0;}
    int LIM = 25e4 + 5;
    vl dp(LIM);
    dp[0] = 1;
    int halfsum = (n + 1) * n / 2 / 2;
    // cout << halfsum << nL;
    rep(i, 1, n + 1){
        int v = i;
        for(int j = halfsum; j - v >= 0; j--){
            dp[j] = mod(dp[j] + dp[j - v]);
        }
    }
    // rep(i, 0, halfsum + 1){
    //     cout << dp[i] << nL;
    // }
    cout << mod(dp[halfsum] * 500000004) << nL;
    
    return 0;
}