#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

#define int long long

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;

ll tri(ll i){
    assert(i >= 0);
    return i * (i + 1) / 2;
}

ll score(ll l1, ll r1, ll l2, ll r2){
    // if(r2 < l1) return 0;
    // ll l3 = max(l1, l2);
    // ll ans = 0;
    // if(l1 < l2){
    //     ans += (l2 - l1) * (r2 - l2 + 1);
    // }
    // ll r3 = min(r1, r2);
    // ans += tri(r2 - l3);
    // ans -= tri(r2 - r3);
    // return ans;
    if(r2 < l1) return 0;
    l2 = max(l2, l1);
    r1 = min(r1, r2);
    if(l1 > r1 || l2 > r2) {
        return 0;
    }
    ll ans = (r1 - l1 + 1) * (r2 - l2 + 1);
    if(r1 < l2 || r2 < l1){
    }
    else{
        ll overlap = min(r1, r2) - max(l1, l2) + 1;
        ans -= tri(overlap);
    }
    return ans;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; 
    cin >> nc;
    ll lim = 1e18 + 100;
    rep(cn, 0, nc){
        int n; cin >> n;
        vii ranges(n);
        vector<array<int, 3>> events; // x, type, idx
        // should not need multiset if using indices
        set<pii> lefts, rights, glefts, grights;
        rep(i, 0, n){
            cin >> ranges[i].first >> ranges[i].second;
            events.push_back({ranges[i].first, 1, i});
            events.push_back({ranges[i].second + 1, -1, i});
            rights.insert({ranges[i].second, i});
            glefts.insert({ranges[i].first, i});
            grights.insert({ranges[i].second, i});
        }
        if(n == 1){
            cout << 1 << "\n";
            continue;
        }
        ll ans = 0;
        sort(all(events));
        rep(i, 0, sz(events)){
            auto [x, type, idx] = events[i];
            if(type == -1){
                assert(rights.find({x - 1, idx}) != rights.end());
                rights.erase({x - 1, idx});
            }
            else{
                lefts.insert({x, idx});
            }
            ll cont = 0;
            // always should have a left
            vi remidx;
            if(sz(lefts) == 1){
                auto [l, remidx1] = *lefts.begin();
                remidx.push_back(remidx1);
            }
            if(sz(rights) == 1){
                auto [r, remidx1] = *rights.begin();
                remidx.push_back(remidx1);
            }
            assert(sz(rights) != 0 || i + 1 >= sz(events));
            assert(sz(lefts) != 0);
            
            for(int r : remidx){
                glefts.erase({ranges[r].first, r});
                grights.erase({ranges[r].second, r});
            }
            if(sz(glefts) > 0 && sz(grights) > 0){
                auto [l1, g1] = *glefts.begin();
                auto [r1, g2] = *grights.rbegin();
                if(i + 1 < sz(events)){
                    auto [x1, type1, idx1] = events[i + 1];
                    if(x1 > x) {
                        ans += score(x, x1 - 1, l1, r1);
                        assert(score(x, x1 - 1, l1, r1) >= 0 && score(x, x1-1, l1, r1) < lim);
                        // cout << "interval [" << x << "," << (x1-1) << "] to interval [" << l1 << "," << r1 << "] contributes " << score(x,x1-1,l1,r1) << "\n";
                    }
                }
            }
            else{
                assert(n == 2);
            }

            for(int r : remidx){
                glefts.insert({ranges[r].first, r});
                grights.insert({ranges[r].second, r});
            }
        }
        sort(all(ranges));
        if(sz(ranges) == 3 && ranges[0].second < ranges[1].first && ranges[1].second < ranges[2].first){
            ans -= (ranges[1].first - ranges[0].second - 1) * (ranges[2].first - ranges[1].second - 1);
        }
        assert(ans <= lim && ans > 0);
        cout << ans << "\n";
    }

    return 0;
}
