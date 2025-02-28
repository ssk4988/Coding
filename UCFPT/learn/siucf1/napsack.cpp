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
        int n, m; ll x; cin >> n >> m >> x;
        vll sacks(n); // {size, comfort}
        rep(i, 0, n) {
            cin >> sacks[i].s >> sacks[i].f;
        }
        sort(all(sacks));
        reverse(all(sacks));
        {
            vll sacks2;
            for(auto [s, c] : sacks) {
                if(sz(sacks2) == 0 || sacks2.back().s < c) sacks2.pb({s, c});
            }
            sacks = sacks2;
            reverse(all(sacks));
        }
        ll ans = 0;
        rep(i, 0, m) {
            ll w; cin >> w;
            x += w;
            auto it = lower_bound(all(sacks), pll{x, -1});
            if(it != end(sacks)) {
                ans += it->s;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
