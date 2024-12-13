#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// #define int long long
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

struct Line {
    mutable ll k, m, p;
    bool operator< (const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); 
    }
    bool isect(iterator x, iterator y) {
        if(y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        k *= -1, m *= -1;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return -(l.k * x + l.m);
    }
};
using a4 = array<ll, 4>;
const ll inf = 2e18+10;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<a4> ed(m);
    vii states;
    rep(i, 0, m){
        cin >> ed[i][0] >> ed[i][1] >> ed[i][2] >> ed[i][3];
        ed[i][0]--, ed[i][1]--;
        states.push_back({ed[i][0], ed[i][2]});
        states.push_back({ed[i][1], ed[i][3]});
    }
    states.push_back({0, 0});
    sort(all(states));
    states.erase(unique(all(states)), states.end());
    int k = sz(states);
    vector<vii> adj(k);
    vvi radj(k);
    for(auto [a, b, c, d] : ed){
        int s1 = lower_bound(all(states), pii{a, c}) - states.begin();
        int s2 = lower_bound(all(states), pii{b, d}) - states.begin();
        radj[s2].push_back(s1);
    }
    vector<LineContainer> lcs(n);
    lcs[0].add(0, 0);
    ll ans = inf;
    map<int, vi> ts;
    rep(i, 0, k){
        ts[states[i].second].push_back(i);
    }
    vl score(k, -1);
    score[0] = 0;
    for(auto &[key, val] : ts){
        for(int id : val){
            auto [airport, time] = states[id];
            ll curscore = sz(lcs[airport]) == 0 ? inf : lcs[airport].query(time) + ll(time) * time;
            for(int nid : radj[id]){
                auto [nairport, ntime] = states[nid];
                if(score[nid] != -1) {
                    curscore = min(curscore, score[nid]);
                    lcs[airport].add(-2 * time, ll(time) * time + score[nid]);
                }
            }
            score[id] = curscore;
            if(airport == n-1){
                ans = min(ans, curscore);
            }
        }
    }
    if(ans == inf) ans = -1;
    cout << ans << "\n";
    
    return 0;
}
