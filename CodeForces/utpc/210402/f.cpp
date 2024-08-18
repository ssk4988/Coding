#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define f first
#define s second

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vll p(n);
    map<ll, int> xcnt, ycnt;
    rep(i, 0, n){
        cin >> p[i].first >> p[i].second;
        xcnt[p[i].f]++;
        ycnt[p[i].s]++;
    }
    set<pll> pset(all(p));
    ll ans = 0;
    rep(i, 0, n){
        rep(j, 0, i){
            auto [x1, y1] = p[i];
            auto [x2, y2] = p[j];
            if(!(x1 == x2 || y1 == y2)) continue;
            if(x1 == x2){
                ll my = (y1 + y2) / 2;
                if(2 * my != y1 + y2 || !pset.count({x1, my})) continue;
                ans += ycnt[my] - 1;
            }
            if(y1 == y2){
                ll mx = (x1 + x2) / 2;
                if(2 * mx != x1 + x2 || !pset.count({mx, y1})) continue;
                ans += xcnt[mx] - 1;
            }
        }
    }
    cout << ans << "\n";

    return 0;
}