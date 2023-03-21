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

int BLANK = INT_MAX;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    string str; cin >> str;
    if(n * k > str.length()){
        cout << "-1" << nL;
        return 0;
    }
    vector<vvi> dp(k + 1, vvi(n + 1, vi(str.length(), BLANK)));
    dp[0][0][0] = str[0] == 'D';
    dp[0][1][0] = str[0] != 'D';
    rep(l, 0, str.length() - 1){
        rep(i, 0, sz(dp)){
            rep(j, 0, sz(dp[i])){
                if(dp[i][j][l] == BLANK) continue;
                bool thisSwap = (j == 0) != (str[l] == 'G');
                // another duck next
                int j1 = min(n, j + 1);
                dp[i][j1][l + 1] = min(dp[i][j1][l + 1], dp[i][j][l] + (!thisSwap && str[l + 1] != 'D'));

                // G next
                j1 = 0;
                int i1 = j == n ? i + 1 : i;
                i1 = min(i1, k);
                dp[i1][j1][l + 1] = min(dp[i1][j1][l + 1], dp[i][j][l] + (!thisSwap && str[l + 1] != 'G'));
            }
        }
    }
    int ans = BLANK;
    rep(i, 0, sz(dp)){
        rep(j, 0, sz(dp[i])){
            rep(l, 0, sz(dp[i][j])){
                if((i == k - 1 && j == n) || (i == k)){
                    ans = min(ans, dp[i][j][l]);
                }
            }
        }
    }
    if(ans == BLANK) ans = -1;
    cout << ans << nL;
    
    return 0;
}
