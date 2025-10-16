#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

/*
l, r range dp

*/

const ll inf = 1e18+100;
ll safemult(ll a, ll b) {
    if(a == 0 || b == 0) return 0;
    ll maxb = inf / a;
    return b <= maxb ? a*b : inf;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<vl> dp(n+1, vl(n+1));
    rep(i, 0, n) {
        dp[i][i+1] = 1;
    }
    rep(i, 0, n+1) dp[i][i] = 1;
    rep(r, 1, n+1) {
        for(int l = r-2; l >= 0; l--) {
            dp[l][r] = min(inf, dp[l+1][r] + dp[l][r-1]);
        }
    }
    int l = 0, r = n;
    ll k; cin >> k;
    if(k > dp[l][r]) {
        cout << "-1\n";
        return 0;
    }
    vi perm;
    rep(_, 0, n) {
        if(dp[l+1][r] >= k) {
            perm.push_back(l);
            l++;
        } else {
            k -= dp[l+1][r];
            perm.push_back(--r);
        }
    }
    rep(i, 0, n) {
        cout << perm[i]+1 << " ";
    }
    cout << "\n";
    return 0;
}
