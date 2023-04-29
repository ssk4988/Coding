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
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int n; cin >> n;
    vector<vector<ld>> ans(8, vector<ld>(8, 1));
    rep(starti, 0, 8){
        rep(startj, 0, 8){

            vector<vector<vector<ld>>> dp(n + 1, vector<vector<ld>>(8, vector<ld>(8)));
            dp[0][starti][startj] = 1;
            rep(i, 0, n){
                rep(j, 0, 8){
                    rep(k, 0, 8){
                        int nummoves = 0;
                        rep(l, 0, 4){
                            int j1 = j + ds[l][0], k1 = k + ds[l][1];
                            if(j1 >= 0 && j1 < 8 && k1 >= 0 && k1 < 8)nummoves++;
                        }
                        rep(l, 0, 4){
                            int j1 = j + ds[l][0], k1 = k + ds[l][1];
                            if(j1 >= 0 && j1 < 8 && k1 >= 0 && k1 < 8)dp[i + 1][j1][k1] += dp[i][j][k] / nummoves;
                        }
                    }
                }
            }
            rep(i, 0, 8){
                rep(j, 0, 8){
                    ans[i][j] *= 1 - dp[n][i][j];
                }
            }
        }
    }
    ld answer = 0;
    rep(i, 0, 8){
        rep(j, 0, 8){
            answer += ans[i][j];
        }
    }
    cout << fixed << setprecision(6) << answer << nL;
    
    return 0;
}