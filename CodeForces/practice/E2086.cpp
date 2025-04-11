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
const ll lim = 1e18+10;
vl zebra{1};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(zebra.back() < lim) {
        zebra.pb(4*zebra.back()+1);
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ll l, r, k; cin >> l >> r >> k;
        if(k >= 200){
            cout << 0 << "\n";
            continue;
        }
        auto conv = [&](ll x) -> vi {
            vi d(sz(zebra));
            for(int i = sz(zebra)-1; i >= 0; i--) {
                while(zebra[i] <= x) {
                    d[i]++;
                    x -= zebra[i];
                }
            }
            return d;
        };
        l--;
        auto calc = [&](ll x) -> ll {
            vi digs = conv(x);
            vector dp(sz(zebra), vector(2, vl(200, -1)));
            auto go = [&](int dig, int match, int left, auto &&go) -> ll {
                if(left < 0) return 0;
                if(dig == -1) {
                    return left == 0;
                }
                ll &ans = dp[dig][match][left];
                if(ans != -1) return ans;
                ans = 0;
                rep(d, 0, 1+(match ? digs[dig] : 4)) {
                    if(d == 4) {
                        ans += (left-d==0);
                        continue;
                    }
                    ans += go(dig-1, match && d == digs[dig], left - d, go);
                }
                return ans;
            };
            return go(sz(digs)-1, 1, k, go);
        };
        cout << calc(r)-calc(l) << "\n";
    }
    
    return 0;
}
