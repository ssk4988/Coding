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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    a.insert(a.begin(), 0);
    a.pb(0);
    n += 2;
    vvi dp(n + 1, vi(n + 1, 1e9));
    rep(i, 0, n+1){
        dp[i][i] = 0;
    }
    rep(i, 0, n){
        dp[i][i+1] = 1;
    }
    rep(r, 0, n+1){
        for(int l = r; l >= 0; l--){
            int &ans = dp[l][r];
            if(a[l] == a[r-1]){
                if(r-l > 1)ans = min(ans, 1 + dp[l+1][r-1]);
                rep(i, l, r){
                    ans = min(ans, dp[l][i+1] + dp[i][r] - 1);
                }
            }
            rep(i, l, r){
                ans = min(ans, dp[l][i] + dp[i][r]);
            }
        }
    }
    cout << dp[0][n] - 1 << "\n";
    // rep(i, 0, n+1){
    //     rep(j, 0, n+1){
    //         cout << i << " " << j << " " << dp[i][j] << "\n";
    //     }
    // }
    return 0;
}