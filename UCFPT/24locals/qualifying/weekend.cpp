#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ld = long double;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll l, r; cin >> l >> r;
    ll C, N, E; cin >> C >> N >> E;
    ll c, n, e; cin >> c >> n >> e;
    vector dp(c+1, vector(n+1, vector<ld>(e+1, -1)));
    auto go = [&](int i, int j, int k, auto &&go)->ld {
        auto &ans = dp[i][j][k];
        if(ans != -1) return ans;
        ll cur = i * C + j * N + k * E;
        if(cur > r) return ans = 0;
        if(l <= cur && cur <= r) return ans = 1;
        ll left = c + n + e - i - j - k;
        ans = 0;
        if(i < c) ans += (c - i) * go(i+1, j, k, go) / left;
        if(j < n) ans += (n - j) * go(i, j+1, k, go) / left;
        if(k < e) ans += (e - k) * go(i,j,k+1,go) / left;
        // cout << i << " " << j << " " << k << " " << ans << endl;;
        return ans;
    };
    cout << fixed << setprecision(10) << go(0, 0, 0, go) << "\n";

    return 0;
}
