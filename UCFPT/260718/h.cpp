#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const int MOD = 1e9 + 9;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, k; cin >> n >> m >> k;
    vi john(n), paul(m);
    rep(i, 0, n) cin >> john[i];
    rep(i, 0, m) cin >> paul[i];
    sort(all(john));
    sort(all(paul));
    vector dp(n, vector(m, vector(k+1, vector(2, -1))));
    auto go = [&](int i, int j, int left, int move, auto &&go) -> int {
        if(left == 0) return 1;
        if(i == n || j == m) return 0;
        int &ans = dp[i][j][left][move];
        if(ans != -1) return ans;
        ans = 0;
        if(move == 0) (ans += go(i+1, j, left, move, go)) %= MOD;
        (ans += go(i, j+1, left, 1, go)) %= MOD;
        if(john[i] > paul[j]) (ans += go(i+1, j+1, left-1, 0, go)) %= MOD;
        return ans;
    };
    cout << go(0, 0, k, 0, go) << "\n";

    return 0;
}
