#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
const ll mod = 1e9 + 7;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int m, n; cin >> m >> n;
    m *= 4;
    vl dp(m+1);
    dp[0] = 1;
    vi c(n);
    rep(i, 0, n) cin >> c[i];
    rep(j, 0, m){
        rep(i, 0, n){
            if(c[i]+ j < sz(dp)) (dp[c[i]+j] += dp[j]) %= mod;
        }
    }
    cout << dp.back() << "\n";
    return 0;
}