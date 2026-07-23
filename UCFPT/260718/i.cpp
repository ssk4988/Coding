#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    pii laser, barn;
    cin >> n >> laser.first >> laser.second >> barn.first >> barn.second;
    map<int, vii> xs, ys;
    auto ins = [&](pii p) -> void {
        xs[p.first].push_back(p);
        ys[p.second].push_back(p);
    };
    ins(laser), ins(barn);
    vii ps; ps.push_back(laser);
    ps.push_back(barn);
    rep(i, 0, n) {
        pii p; cin >> p.first >> p.second;
        ins(p);
        ps.push_back(p);
    }
    for(auto &[k, v] : xs) sort(all(v));
    for(auto &[k, v] : ys) sort(all(v));
    using state = pair<pii, int>;
    priority_queue<pair<int, state>, vector<pair<int, state>>, greater<>> pq;
    pq.push({0, {laser, 0}});
    pq.push({0, {laser, 1}});
    set<state> seen;
    while(sz(pq)) {
        auto [d, u] = pq.top(); pq.pop();
        if(seen.count(u)) continue;
        auto [p, dir] = u;
        if(p == barn) {
            cout << d << "\n";
            return 0;
        }
        seen.insert(u);
        // cerr << p.first << " " << p.second << " " << dir << " dist " << d << endl;
        pq.push({d+1, {p, dir^1}});
        if(dir == 0) {
            auto it = upper_bound(all(xs[p.first]), p);
            if(it != end(xs[p.first])) pq.push({d, {*it, dir}});
            it--;
            if(it != begin(xs[p.first])) {
                it--;
                pq.push({d, {*it, dir}});
            }

        }
        if(dir == 1) {
            auto it = upper_bound(all(ys[p.second]), p);
            if(it != end(ys[p.second])) pq.push({d, {*it, dir}});
            it--;
            if(it != begin(ys[p.second])) {
                it--;
                pq.push({d, {*it, dir}});
            }

        }
    }
    cout << "-1\n";

    return 0;
}
