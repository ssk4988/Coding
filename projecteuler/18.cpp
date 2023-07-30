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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vvi dp(15);
    rep(i, 0, 15){
        dp[i] = vi(i + 1);
        rep(j, 0, i + 1){
            cin >> dp[i][j];
            if(i){
                dp[i][j] += max(j ? dp[i - 1][j - 1] : 0, j == i ? 0 : dp[i - 1][j]);
            }
        }
    }
    int ans = 0;
    rep(i, 0, 15) ans = max(ans, dp.back()[i]);
    cout << ans << nL;
    
    return 0;
}
