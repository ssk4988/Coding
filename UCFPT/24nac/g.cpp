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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; ld p; cin >> r >> c >> p;
    vector<vd> dp(r, vd(c, -1));
    dp[0][0] = 0;
    auto go = [&](int rl, int cl, auto &&go) -> ld {
        if(rl < 0 || cl < 0) return 1e18;
        ld &ans = dp[rl][cl];
        if(ans != -1) return ans;
        ld r1 = go(rl-1, cl, go), c1 = go(rl, cl-1, go);
        ld dif1 = max(0.0L, min(p, r1 - c1));
        ld p1 = dif1 / p;
        ld dif2 = max(0.0L, min(p, c1 - r1));
        ld p2 = dif2 / p;
        ans = 0.5 * ((1 - p1) * r1 + p1 * c1 + p1 * dif1 / 2)
            + 0.5 * ((1 - p2) * c1 + p2 * r1 + p2 * dif2 / 2);
        return ans;
    };
    cout << fixed << setprecision(10) << go(r-1, c-1, go) << "\n";
    
    return 0;
}
