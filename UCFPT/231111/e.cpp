#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

using vl = vector<ll>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int maxn = 18, maxk = 18;
    vector<vl> dp(maxn, vl(maxk));
    dp[0][0] = 1;
    rep(i, 1, maxn){
        dp[i][0] = i * dp[i-1][0];
        rep(j, 1, i + 1){
            dp[i][j] = dp[i][j-1] - dp[i-1][j-1];
        }
    }
    rep(_, 0, nc){
        int cn, n, k; cin >> cn >> n >> k;
        cout << cn << " " << dp[n][k] << "\n";
    }
    return 0;
}
