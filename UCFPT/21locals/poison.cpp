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
    k = min(k, 40);
    const int bad = -1;
    vvi dp(n+1, vi(k+1, bad));
    auto go = [&](int len, int left, auto &&go) -> int {
        int &ans = dp[len][left];
        if(ans != -1) return ans;
        ans = 1e9;
        if(len == 1) return ans = 0;
        if(left == 0) return ans;
        if(left == 1) return ans = len-1;
        pii opt = {1e9, -1};
        rep(split, 1, len) {
            int v = 1+max(go(split, left-1, go), go(len-split, left, go));
            ans = min(ans, v);
            opt = min(opt, {v, split});
        }
        if(len == n) {
            cout << len << " " << left << " " << opt.first << " " << opt.second << endl;
        }
        return ans;
    };
    cout << go(n, k, go) << "\n";

    return 0;
}