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

int dp[5010][5010];
bool u[5010][5010];
int c[5010][3];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int l, t;
    cin >> l >> t;
    memset(dp, -1, sizeof dp);
    memset(u, false, sizeof u);
    rep(i, 0, t)
    {
        rep(j, 0, 3)
        {
            cin >> c[i][j];
        }
    }
    dp[0][0] = 0;
    dp[1][0] = c[0][0];
    dp[2][0] = c[0][1];
    dp[3][0] = c[0][2];
    u[0][0] = true;
    u[1][0] = true;
    u[2][0] = true;
    u[3][0] = true;
    rep(i, 0, l + 1)
    {
        rep(j, 0, t)
        {
            if(j-1>=0&&u[i][j-1]){
                if(u[i][j]){
                    dp[i][j] = min(dp[i][j], dp[i][j-1]);
                }
                else{
                    u[i][j] = true;
                    dp[i][j] = dp[i][j-1];
                }
            }
            if(j-1>=0&&i-1>=0&&u[i-1][j-1]){
                if(u[i][j]){
                    dp[i][j] = min(dp[i][j], dp[i-1][j-1]+c[j][0]);
                }
                else{
                    u[i][j] = true;
                    dp[i][j] = dp[i-1][j-1]+c[j][0];
                }
            }
            if(j-1>=0&&i-2>=0&&u[i-2][j-1]){
                if(u[i][j]){
                    dp[i][j] = min(dp[i][j], dp[i-2][j-1]+c[j][1]);
                }
                else{
                    u[i][j] = true;
                    dp[i][j] = dp[i-2][j-1]+c[j][1];
                }
            }
            if(j-1>=0&&i-3>=0&&u[i-3][j-1]){
                if(u[i][j]){
                    dp[i][j] = min(dp[i][j], dp[i-3][j-1]+c[j][2]);
                }
                else{
                    u[i][j] = true;
                    dp[i][j] = dp[i-3][j-1]+c[j][2];
                }
            }
        }
    }
    int ans = 1000000000;
    rep(i, 0, t + 1) // check only valid values?
    {
        if (u[l][i])
        {
            ans = min(ans, dp[l][i]);
            //cout << dp[l][i] << nL;
        }
    }
    cout << ans << nL;

    return 0;
}