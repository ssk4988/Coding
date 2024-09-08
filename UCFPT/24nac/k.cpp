#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vl = vector<ll>;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ld = long double;
using vd = vector<ld>;

const ld oo = 1e20;

pair<ld, ld> halfplane_range(pair<ld, ld> u, pair<ld, ld> v) {
    auto [x1, y1] = u;
    auto [x2, y2] = v;
    ld x = x1 - y1*(x2-x1)/(y2-y1);
    x = min(x, 0.0l);
    if (y2 > y1) return {-oo, x};
    else return {x, 0};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll w; cin >> n >> w;
    // ll?
    vector<array<pair<ld, ld>, 2>> arr;
    rep(i, 0, n) {
        int x, yl, yh; cin >> x >> yl >> yh;
        arr.push_back(array{pair<ld, ld>{x, yl}, pair<ld, ld>{x, yh}});
    }
    vector<pair<ld, int>> bad_ranges;
    rep(i, 0, n){
        // cerr << i << endl;
        vector<pair<ld, int>> evs;
        rep(j, 0, n){
            if(i == j) continue;
            auto u = arr[i], v = arr[j];
            auto [l1, r1] = halfplane_range(u[1], v[0]);
            auto [l2, r2] = halfplane_range(v[1], u[1]);
            // cerr << j << ": " << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
            evs.insert(evs.end(), {{l1, 1}, {r1, -1}, {l2, 2}, {r2, -2}});
        }
        sort(all(evs));
        int ones = 0, twos = 0;
        ld prv = -oo;
        for (auto [x, t] : evs) {
            // cerr << x << " " << t << endl;
            if (ones && ones+twos == n-1) {
                bad_ranges.push_back({prv, 1});
                bad_ranges.push_back({x, -1});
                // cerr << "added " << prv << "->" << x << endl;
            }
            if (t == 1) ones++;
            else if (t == -1) ones--;
            else if (t == 2) twos++;
            else if (t == -2) twos--;
            prv = x;
        }
    }
    sort(all(bad_ranges));
    if (bad_ranges.empty() || bad_ranges[0].first != -oo) {
        cout << "-1\n";
        return 0;
    }
    ld prv = -oo;
    ld res = 0;
    int tot = 0;
    for (auto [x, t] : bad_ranges) {
        // cerr << x << " " << t << endl;
        if (tot == 0) res += x-prv;
        tot += t;
        prv = x;
    }
    res += 0-prv;
    cout << setprecision(20) << fixed << res << "\n";

    return 0;
}