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
        int n; cin >> n;
        vvi a(n, vi(n));
        // vvi a2(n, vi(n));
        rep(i, 0, n){
            rep(j, 0, n){
                cin >> a[i][j];
                // a2[n - 1 - j][i] = a[i][j];
            }
        }
        if(n == 2){
            cout << (a[0][0] ^ a[1][0]) << nL;
            continue;
        }
        int ans = 0;
        rep(x, 0, 2){
            vvi dp(n, vi(n, -1));
            // vector<FT> fts;
            rep(y, 0, 2){
                rep(d, 1, n){
                    int sum = 0;
                    rep(v, 0, d){
                        int i = d - 1 - v, j = v;
                        sum ^= a[i][j];
                    }
                    rep(v, 0, (d + 1) / 2){
                        int i = d - v, j = v;
                        dp[i][j] = dp[j][i] = sum ^ (i > 0 && j > 0 ? dp[i-1][j-1] : 0);
                        sum ^= a[i-1][j];
                        sum ^= a[j][i - 1];
                    }
                    // fts.pb(FT(min(d + 1, 2 * n - 1 - d)));
                }
                rep(i, 0, n){
                    rep(j, 0, n){
                        if(i + j < n){
                            swap(a[i][j], a[n - 1 - i][n - 1 - j]);
                            swap(dp[i][j], dp[n - 1 - i][n - 1 - j]);
                        }
                    }
                }
            }
            if(x == 0){
                rep(i, 0, n){
                    rep(j, 0, n){
                        if(i < j) ans ^= dp[i][j];
                    }
                }
            }
            else{
                rep(i, 0, n/2){
                    ans ^= dp[i][n - 1 - i];
                }
            }
            vvi a2(a);
            rep(i, 0, n){
                rep(j, 0, n){
                    a[n - 1 - j][i] = a2[i][j];
                }
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
