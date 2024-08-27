#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ld = long double;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; ll m; cin >> n >> k >> m;
    vector<pii> p(n);
    rep(i, 0, n){
        cin >> p[i].first >> p[i].second;
    }
    vector<vector<pair<int, ld>>> o(n);
    rep(i, 0, n){
        ld d = sqrtl((p[i].first - p[(i+1)%n].first) * (p[i].first - p[(i+1)%n].first) + (p[i].second - p[(i+1)%n].second) * (p[i].second - p[(i+1)%n].second));
        o[i].push_back({(i+1)%n, d});
        o[(i+1)%n].push_back({i, d});
    }
    vector<array<int, 3>> r(k);
    rep(i, 0, k){
        rep(j, 0, 3) cin >> r[i][j];
        r[i][0]--, r[i][1]--;
    }
    ll ans = 1e15;
    rep(mask, 0, 1 << k){
        auto g(o);
        ll cost = 0;
        rep(i, 0, k){
            if((mask >> i) & 1) {
                auto [p1, p2, c] = r[i];
                cost += c;
                ld d = sqrtl((p[p1].first - p[p2].first) * (p[p1].first - p[p2].first) + (p[p1].second - p[p2].second) * (p[p1].second - p[p2].second));
                g[p1].push_back({p2, d});
                g[p2].push_back({p1, d});
            }
        }
        vector<vector<ld>> best(n, vector<ld>(n, 1e18));
        rep(i, 0, n){
            for(auto [j, d] : g[i]){
                best[i][j] = min(best[i][j], d);
            }
            best[i][i] = 0;
        }
        rep(l,0,n){
            rep(i,0,n){
                rep(j,0,n){
                    best[i][j] = min(best[i][j], best[i][l] + best[l][j]);
                }
            }
        }
        bool works = true;
        rep(i, 0, n){
            rep(j,0, n){
                if(best[i][j] > m){
                    works = false;
                }
            }
        }
        if(works) ans = min(ans, cost);
    }
    cout << ans << "\n";

    return 0;
}
