#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; ll a, b; cin >> n >> a >> b;
        vector dp(n, vector(n, vl(2, -1)));
        vl v(n); 
        rep(i, 0, n) cin >> v[i];
        auto go = [&](int l, int r, int p, auto &&go) -> ll {
            ll &ans = dp[l][r][p];
            if(ans != -1) return ans;
            ans = 0;
            if(l == r) return ans;
            rep(i, 0, 2) {
                bool diff = (l == 0 && r == n-1 || i != p);
                int l1 = l+(i == 0), r1 = r-(i == 1);
                ans = max(ans, go(l1, r1, i, go) + (diff ? b : a) * v[l1] * v[r1]);
            }
            return ans;
        };
        cout << go(0, n-1, 0, go) << "\n";
    }
    
    return 0;
}
