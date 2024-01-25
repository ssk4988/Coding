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

template<typename T>
void chmin(T &a, const T& b) {
    if(b < a) a = b;
}

int dp[100][100][100][2];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, x; cin >> n >> x;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
        }
        // vector<vector<vvi>> dp(n, vector<vvi>(n, vvi(x, vi(2, 1e9))));
        rep(i, 0, n){
            rep(j, 0, x){
                dp[i][i][j][0] = a[i] == j;
                dp[i][i][j][1] = a[i] != j;
            }
        }
        rep(r, 0, n){
            for(int l = r - 1; l >= 0; l--) {
                rep(i, 0, x){
                    dp[l][r][i][0] = dp[l][r][i][1] = 1e9;
                    rep(r1, l, r){
                        chmin(dp[l][r][i][0], dp[l][r1][i][0] + dp[r1 + 1][r][i][0]);
                        chmin(dp[l][r][i][0], dp[l][r1][i][0] + dp[r1 + 1][r][i][1] + 1);
                        chmin(dp[l][r][i][0], dp[l][r1][i][1] + dp[r1 + 1][r][i][0] + 1);
                        // chmin(dp[l][r][i][0], dp[l][r1][i][1] + dp[r1 + 1][r][i][1] + 1);
                        // chmin(dp[l][r][i][1], dp[l][r1][i][0] + dp[r1 + 1][r][i][0] + 1);
                        chmin(dp[l][r][i][1], dp[l][r1][i][0] + dp[r1 + 1][r][i][1] + 1);
                        chmin(dp[l][r][i][1], dp[l][r1][i][1] + dp[r1 + 1][r][i][0] + 1);
                        chmin(dp[l][r][i][1], dp[l][r1][i][1] + dp[r1 + 1][r][i][1]);
                    }
                }
                rep(i, 0, x){
                    rep(j, 0, x){
                        if(i == j) {
                            continue;
                        }
                        else{
                            // chmin(dp[l][r][i][0], dp[l][r][j][0] + 1);
                            chmin(dp[l][r][i][0], dp[l][r][j][1]);
                            // chmin(dp[l][r][i][1], dp[l][r][j][0] + 2);
                            chmin(dp[l][r][i][1], dp[l][r][j][1] + 1);
                        }
                    }
                    chmin(dp[l][r][i][0], dp[l][r][i][1] + 1);
                    chmin(dp[l][r][i][1], dp[l][r][i][0] + 1);
                }
            }
        }
        int ans = 1e9;
        rep(i, 0, x){
            chmin(ans, dp[0][n-1][i][1]);
        }
        cout << ans << nL;
    }
    
    return 0;
}
