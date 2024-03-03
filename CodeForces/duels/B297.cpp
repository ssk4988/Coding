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
    string str; cin >> str;
    vector<vvi> dp(n+1, vvi(3, vi(2)));
    rep(i, 0, n){
        rep(j, 0, 3){
            int b = str[i] - '0';
            if(j == 1) b = 1 - b;
            rep(k, 0, 2){
                dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k]);
                if(j + 1 < 3){
                    dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k]);
                }
            }
            dp[i+1][j][b] = max(dp[i+1][j][b], 1 + dp[i][j][1 - b]);
            if(j+1 < 3){
                dp[i+1][j+1][b] = max(dp[i+1][j+1][b], 1 + dp[i][j][1 - b]);
            }
        }
    }
    int best = 0;
    rep(i, 0, 3){
        rep(j, 0, 2){
            best = max(best, dp[n][i][j]);
        }
    }
    cout << best << "\n";
    
    return 0;
}