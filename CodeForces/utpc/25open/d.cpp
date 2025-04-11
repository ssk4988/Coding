#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; int d; cin >> n >> d;
    vii p(n);
    rep(i, 0 ,n){
        cin >> p[i].first >> p[i].second;
    }
    sort(all(p));
    int prv = -1;
    vl dp(n);
    rep(i, 0, n) {
        while(prv+1 < n && p[prv+1].first + d <= p[i].first) {
            prv += 1;
        }
        dp[i] = p[i].second;
        if(prv >= 0) dp[i] += dp[prv];
        if(i) dp[i] = max(dp[i], dp[i-1]);
    }
    cout << dp.back() << "\n";

    return 0;
}
