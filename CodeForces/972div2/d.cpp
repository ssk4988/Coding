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
        int n; cin >> n;
        vi a(n), b(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        rep(i, 0, n) cin >> b[i];
        // a.insert(begin(a), 0);
        // b.insert(begin(b), 0);
        // n++;
        map<array<int, 3>, ll> dp;
        dp[{0, 0, 0}] = 1;
        dp[{0, 0, 1}] = 1;
        rep(i, 0, n) {
            map<array<int, 3>, ll> new_dp;
            for(auto &[key, val] : dp) {
                const auto &[g1, g2, t] = key;
                // cerr << i << " " << g1 << " " << g2 << " " << t << " " << val << endl;
                if(t == 1) {
                    int h1 = gcd(g1, b[i]), h2 = gcd(g2, a[i]);
                    new_dp[{h1, h2, t}] += val;
                    new_dp[{h1, h2, t+1}] += val;
                } else {
                    int h1 = gcd(g1, a[i]), h2 = gcd(g2, b[i]);
                    new_dp[{h1, h2, t}] += val;
                    if(t == 0) {
                        new_dp[{h1, h2, t+1}] += val;
                    }
                }
            }
            dp = new_dp;
        }
        pair<int,ll> ans{-1, -1};
        for(auto [key, val] : dp) {
            auto [h1, h2, t] = key;
            if(t != 2) continue;
            if(h1 + h2 > ans.first) ans = {h1 + h2, val};
            else if(h1 + h2 == ans.first) ans.s += val;
        }
        cout << ans.f << " " << ans.s << "\n";
    }
    
    return 0;
}
