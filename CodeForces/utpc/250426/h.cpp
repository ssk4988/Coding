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
    int n; cin >> n;
    set<int> xs;
    set<pii> ps;
    map<int, set<int>> cols;
    vii input;
    set<pii> trav, seen;
    rep(i, 0, n) {
        int x, y; cin >> x >> y;
        ps.insert({x, y});
        xs.insert(x);
        xs.insert(x-1);
        xs.insert(x+1);
        input.pb({x, y});
    }
    for(auto [x, y] : input) {
        for(int x1 : {x-1, x, x+1}){
            if(!ps.count({x1, y+1})) {
                trav.insert({x1, y+1});
                // cols[x1].insert(y+1);
            }
        }
        trav.insert({x, y});
        // cols[x].insert(y);
    }
    int q; cin >> q;
    vii qs(q);
    rep(i, 0, q) {
        cin >> qs[i].f >> qs[i].s;
        auto [x, y] = qs[i];
        trav.insert({x, y});
    }
    for(int x : xs) {
        if(!ps.count({x, 1})){
            // cols[x].insert(1);
            trav.insert({x, 1});
        }
    }
    using a3 = array<int, 3>;
    // end at bottom
    for(auto [x, y] : trav) {
        if(ps.count({x, y})) continue;
        if(y > 1) continue;
        pq.push({0, x, y});
    }
    // end at 
    // min, max
    map<pii, pii> dp;
    auto go = [&](int x, int y, auto &&go) -> pii {
        pii key{x, y};
        if(dp.count(key)) return dp[key];
        pii& ans = dp[key];
        if(y == 1 || ps.count({x-1, y}) || ps.count({x+1, y})) return ans = pii{0, 0};
        ans.f = 1e9;
        ans.s = -1e9;
        // fall
        auto it = trav.lower_bound({x, y});
        if(it != begin(trav)) {
            it--;
            auto [x1, y1] = *it;
            if(x1 == x && !ps.count({x1, y1})) {
                auto [mn, mx] = go(x1, y1, go);
                ans.f = min(ans.f, mn + y-y1);
                ans.s = max(ans.s, mx + y-y1);
            }
        }
        for(int x1 : {x-1, x+1}){
            if(ps.count({x1, y})) continue;
            auto [mn, mx] = go(x1, y, go);
            ans.f = min(ans.f, mn + y-y);
            ans.s = max(ans.s, mx + y-y);
        }
        return ans;
    };
    rep(i, 0, q) {
        auto [mn, mx] = go(qs[i].f, qs[i].s, go);
        cout << mx << " " << mn << "\n";
    }

    return 0;
}
