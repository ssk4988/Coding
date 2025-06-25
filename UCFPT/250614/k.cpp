#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        const ll inf = 1e9+10;
        ll p; int n; cin >> p >> n;
        map<ll, int> freq;
        rep(i, 0, n) {
            int v; cin >> v;
            freq[v] += 1;
        }
        vector<pair<ll, ll>> events;
        for(auto [key, val] : freq) {
            events.push_back({key, val});
        }
        events.push_back({-3 * inf, 0});
        events.push_back({3 * inf, 0});
        sort(all(events));
        ll left = 0, right = n;
        ll cur = 0;
        for(auto [x, cnt] : events) {
            cur += (x-events[0].first) * cnt;
        }
        ll ans = 0;
        rep(i, 0, sz(events)-1) {
            auto [l, cnt1] = events[i];
            auto [r, cnt2] = events[i+1];
            left += cnt1, right -= cnt1;
            ll x = l;
            ll delta = left - right;
            // cerr << cn << ": l=" << l << " r=" << r << " left=" << left << " right=" << right << " delta=" << delta << " cur=" << cur << " ans=" << ans << " " << endl;
            while(x < r) {
                // cerr << "at " << x << " ans=" << ans << " cur=" << cur << endl;
                if(cur <= p && delta <= 0) {
                    // cerr << "case0" << endl;
                    ans += r-x;
                    cur += (r-x) * delta;
                    x = r;
                }
                else if(cur > p && delta > 0) {
                    // cerr << "case1" << endl;
                    cur += (r-x) * delta;
                    x = r;
                } else if(cur <= p && delta > 0) {
                    ll adv = min(r-x, (p+1 - cur + delta-1)/delta);
                    // cerr << "case2 " << adv << endl;
                    ans += adv;
                    cur += adv * delta;
                    x += adv;
                } else if(cur > p && delta <= 0) {
                    // cerr << "case3" << endl;

                    if(delta == 0) {
                        cur += (r-x) * delta;
                        x = r;
                    } else {
                        ll adv = min(r-x, (cur - p + abs(delta)-1)/abs(delta));
                        cur += adv * delta;
                        x += adv;
                    }
                } else assert(false);
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
