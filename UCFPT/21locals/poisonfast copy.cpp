#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k; cin >> n >> k;
    k = min(k, 20);
    const int bad = -1;
    vvi dp(n+1, vi(k+1, bad));
    auto go = [&](int len, int left, auto &&go) -> int {
        int &ans = dp[len][left];
        if(ans != -1) return ans;
        ans = 1e9;
        if(len == 1) return ans = 0;
        if(left == 0) return ans;
        if(left == 1) return ans = len-1;
        int lim = len;
        if(left > 1) {
            lim = min(lim, int(pow(len, 1-1/left)));
        }
        rep(split, max(1, lim-100), min(len, lim+100)) {
            ans = min(ans, 1+max(go(split, left-1, go), go(len-split, left, go)));
            ans = min(ans, 1+max(go(split, left, go), go(len-split, left-1, go)));
        }
        return ans;
    };
    cout << go(n, k, go) << "\n";

    return 0;
}