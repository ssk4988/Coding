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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n;
        cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        int BLANK = -1;
        vvi dp(n + 1, vi(n, BLANK));
        dp[0][0] = 1;
        rep(j, 0, n){
            dp[1][j] = 1;
        }
        int rnmx = 0;
        rep(i, 0, n + 1){
            rep(j, 0, n){
                if(dp[i][j] == BLANK) continue;

                if(i + 1 <= n) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                if(j + 1 < n && a[j] < a[j + 1]){
                    dp[i][j + 1] = max(dp[i][j + 1], 1 + dp[i][j]);
                }
                rep(j1, j + 2, n){
                    if(i + 1 <= n && a[j] < a[j1]){
                        dp[i + 1][j1] = max(dp[i + 1][j1], 1 + dp[i][j]);
                    }
                }
            }
        }
        rep(i, 0, n + 1){
            rnmx = max(rnmx, dp[i][n - 1]);
            if(i) cout << (n - rnmx) << " ";
            rep(j, 0, n - 1){
                rnmx = max(rnmx, dp[i][j]);
            }
        }
        cout << nL;
    }
    
    return 0;
}
