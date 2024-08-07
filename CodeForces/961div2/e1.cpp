#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;
using vvl = vector<vl>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n * 2);
        rep(i, 0, sz(a)){ 
            cin >> a[i];
        }
        if(n == 1) {
            cout << 0 << "\n";
            continue;
        }
        if(n % 2 == 0){
            ll mn = LLONG_MAX, mx = LLONG_MIN;
            for(int i = 0; i < n; i += 2){
                vl b = {a[i], a[i+1], a[n + i], a[n + i + 1]};
                vl c = {b[0] + b[1], b[2] + b[3]};
                vl d = {b[0] + b[3], b[1] + b[2]};
                sort(all(c));
                sort(all(d));
                if(c[0] < d[0]){
                    swap(c, d);
                }
                mn = min(mn, c[0]);
                mx = max(mx, c[1]);
            }
            cout << (mx - mn) << "\n";
            continue;
        }
        vl order;
        order.pb(a[0]);
        order.pb(a[n]);
        int cur = n ^ 1;
        while(cur != 0){
            order.pb(a[cur]);
            if(cur >= n) cur -= n;
            else cur += n;
            order.pb(a[cur]);
            cur ^= 1;
        }
        rotate(order.begin(), order.begin() + 1, order.end());
        // rep(i, 0, sz(order)){
        //     cout << order[i] << " ";
        // }
        // cout << "\n";
        auto sw = [&](int idx, int swapped) -> ll {
            return swapped ? (idx == 0 ? order.back() : order[idx - 1]) : order[idx];
        };
        vector<vvl> dp(sz(order), vvl   (2, vl(2, -1)));
        auto solve = [&](ll minlim) -> ll {
            for(int idx = sz(order) - 2; idx >= 0; idx -= 2) {
                rep(prev, 0, 2){
                    rep(first, 0, 2){
                        ll &ans = dp[idx][prev][first];
                        // if(ans != -1) return ans;
                        ans = LLONG_MAX;
                        if(idx == sz(order) - 2) {
                            if(sw(idx, prev) + (first ? order[0] : order.back()) >= minlim) {
                                ans = sw(idx, prev) + (first ? order[0] : order.back());
                            }
                            continue;
                        }
                        // memo check
                        ans = LLONG_MAX;
                        if(sw(idx, prev) + order[idx + 1] >= minlim) {
                            ans = min(ans, max(sw(idx, prev) + order[idx + 1], dp[idx + 2][0][first]));
                        }
                        if(sw(idx, prev) + order[idx + 2] >= minlim) {
                            ans = min(ans, max(sw(idx, prev) + order[idx + 2], dp[idx + 2][1][first]));
                        }

                    }
                }
            }
            ll ans = min(dp[0][0][0], dp[0][1][1]);
            return ans - minlim;
        };
        ll best = LLONG_MAX;
        vl pos;
        for(int i = 0; i < sz(order); i += 2){
            vl p1 = {order[i], i == 0 ? order.back() : order[i - 1]};
            vl p2 = {order[i + 1], i + 2 == sz(order) ? order[0] : order[i + 2]};
            for(ll x : p1){
                for(ll y : p2){
                    pos.pb(x + y);
                    // best = min(best, solve(x + y));
                }
            }
        }
        sort(all(pos));
        // pos.erase(unique(all(pos)), pos.end());
        for(auto y : pos){
            best = min(best, solve(y));
        }
        // cout << sz(pos) << "\n";
        cout << best << "\n";
    }
    
    return 0;
}
