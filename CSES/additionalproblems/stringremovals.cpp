#include <bits/stdc++.h>
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
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = sz(str);
    vi last(26, n + 1);
    vvi trans(n + 1, vi(26, -1));
    for(int i = n; i >= 0; i--){
        rep(j, 0, 26) trans[i][j] = last[j];
        if(i) last[str[i - 1] - 'a'] = i;
    }
    vl dp(n + 1);
    dp[0] = 1;
    ll sum = 0;
    rep(i, 0, n + 1){
        rep(j, 0, 26){
            if(trans[i][j] <= n){
                dp[trans[i][j]] = mod(dp[trans[i][j]] + dp[i]);
            }
        }
        // cout << i << " " << dp[i] << "\n";
        if(i) sum = mod(sum + dp[i]);
    }
    cout << sum << "\n";
    
    return 0;
}