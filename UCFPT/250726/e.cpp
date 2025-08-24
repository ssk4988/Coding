#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
using pll = pair<ll, ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vl a(4);
    rep(i, 0, 4) cin >> a[i];
    vector<pll> trans = {
        {0b0001, a[0]},
        {0b0010, a[0]},
        {0b0100, a[0]},
        {0b1000, a[0]},
        {0b0011, a[1]},
        {0b1100, a[1]},
        {0b0101, a[2]},
        {0b1010, a[2]},
        {0b1111, a[3]},
    };
    // 01
    // 23
    const ll inf = 1e18;
    // min cost to get to this state from 0
    vl flip(16, inf);
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> pq;
    pq.push({0, 0});
    
    while(sz(pq)) {
        auto [d, at] = pq.top(); pq.pop();
        if(flip[at] != inf) continue;
        flip[at] = d;
        // cerr << mask << " " << at << " " << d << endl;
        for(auto [change, cost] : trans) {
            int nxt = at ^ change;
            pq.push({d + cost, nxt});
        }
    }
    vector dp(1 << 16, vl(16, inf));
    // dp[0][17] = 0;
    rep(i, 1, 16) {
        dp[1 << i][i] = flip[i];
    }
    rep(mask, 1, 1 << 16) {
        rep(at, 0, 16) {
            if(!((mask >> at)&1)) continue;
            rep(prv, 0, 16) {
                if(prv == at) continue;
                if(!((mask >> prv)&1)) continue;
                ll cost = flip[prv^at];
                dp[mask][at] = min(dp[mask][at], dp[mask ^ (1 << at)][prv] + cost);
            }
        }
    }
    vl dist(1 << 16, inf);
    rep(mask, 0, 1 << 16) {
        rep(i, 0, 16)
            dist[mask] = min(dist[mask], dp[mask][i]);
    }
    rep(bit, 0, 16) {
        for(int mask = (1 << 16)-1; mask >= 0; mask--) {
            if((mask >> bit)&1) {
                dist[mask ^ (1 << bit)] = min(dist[mask ^ (1 << bit)], dist[mask]);
            }
        }
    }
    rep(cn, 0, nc) {
        int m; cin >> m;
        int mask = 0;
        rep(i, 0, m) {
            string s1, s2; cin >> s1 >> s2;
            int cur = (s1[0]-'0') + ((s1[1]-'0')<<1) + ((s2[0]-'0')<<2) + ((s2[1]-'0')<<3);
            cur ^= (1 << 4)-1;
            mask |= 1 << cur;
        }
        cout << dist[mask] << "\n";
    }

    return 0;
}
