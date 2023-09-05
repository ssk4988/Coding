#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ld = long double;
using vvi = vector<vi>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define pb push_back
#define f first
#define s second

// pi cmp(pi &a, pi &b){
//     if(a.f != b.f) return max(a, b);
//     return min(a, b);
// }

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vvi dp(n, vi(n, -1));
        rep(i, 0, n){
            dp[i][i] = 1;
        }
        // cout << "Case: " << (cn + 1) << "\n";
        for(int i = n - 1; i >= 0; i--){
            rep(j, i + 1, n){
                rep(k, i + 1, j + 1){
                    if(a[i] < a[k] && dp[k][j] != -1){
                        dp[i][j] = max(dp[i][j], 1 + dp[k][j]);
                    }
                }
                // cout << "dp[" << i << "][" << j << "]=" << dp[i][j] << "\n";
            }
        }
        rep(k, 1, n + 1){
            // vi dp1(n + 1);
            vi dp1(n);
            rep(i, 0, n){
                if(i) dp1[i] = max(dp1[i], dp1[i - 1]);
                rep(j, 0, i + 1){
                    if(dp[j][i] >= k){
                        dp1[i] = max(dp1[i], dp[j][i] + (j ? dp1[j - 1] : 0));
                    }
                }
            }
            cout << dp1[n - 1] << " ";
        }
        cout << "\n";
    }
}
