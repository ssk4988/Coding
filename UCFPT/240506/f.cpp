#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int LIM = 2e5 + 100;
    vi composite(LIM);
    composite[0] = composite[1] = true;
    rep(i, 2, LIM){
        if(ll(i) * i < LIM && !composite[i]){
            for(int j = i * i; j < LIM; j += i){
                composite[j] = true;
            }
        }
    }
    int n; cin >> n;
    vi a(n);
    vvi dp(n);
    // 0 self
    // 1 change 1
    // 2 change even
    // 3 change odd not 1
    rep(i, 0, n){
        cin >> a[i];
    }
    dp[0] = vi(4, 1);
    dp[0][0] = 0;
    const int inf = 1e9;
    rep(i, 1, n){
        dp[i] = vi(4, i);
        if(!composite[a[i] + a[i-1]]) dp[i][0] =min(dp[i][0], dp[i-1][0]);
        if(!composite[a[i]+1]) dp[i][0] = min(dp[i][0], dp[i-1][1]);
        if(a[i] % 2 == 1) dp[i][0] = min(dp[i][0], dp[i-1][2]);
        if(a[i] % 2 == 0) dp[i][0] = min(dp[i][0], dp[i-1][3]);
        dp[i][1] = 1 + min({dp[i][1], dp[i-1][1], dp[i-1][2], !composite[a[i-1] + 1] ? dp[i-1][0] : inf});
        dp[i][2] = 1 + min({dp[i][2], dp[i-1][1], dp[i-1][3], a[i-1] % 2 == 1 ? dp[i-1][0] : inf});
        dp[i][3] = 1 + min({dp[i][3], dp[i-1][2], a[i-1] % 2 == 0 ? dp[i-1][0] : inf});
    }
    int ans = n;
    rep(i, 0, n){
        rep(j, 0, 4){
            ans = min(ans, n - 1 - i + dp[i][j]);
        }
    }
    cout << ans << "\n";

    return 0;
}
