#include <bits/stdc++.h>
using namespace std;

#define double long double

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct pt {
    ll x, y;
    pt(ll x = 0, ll y = 0): x(x), y(y) {}
    ll dist2() { return x*x + y*y; }
    pt operator-(pt p) const { return pt(x - p.x, y - p.y); }
    pt operator+(pt p) const { return pt(x + p.x, y + p.y); }
    pt operator*(ll c) const { return pt(x * c, y * c); }
    bool operator<(pt p) const { return tie(x, y) < tie(p.x, p.y); }
    ll cross(pt p) {
        return x * p.y - y * p.x;
    }
};

const double eps = 1e-12;

struct upper_circle {
    pt c; ll r; int idx;
    upper_circle(ll x=0, ll y=0, ll r=0, int i=-1): c(x, y), r(r), idx(i) {}
    double f(ll x) const  { return c.y + sqrtl(r*r - (x-c.x)*(x-c.x)); }
    ll left() const { return c.x - r; }
    bool operator<(upper_circle o) const {
        if(r < o.r) {
            if(c.y == o.c.y && (c - o.c).dist2() == (r + o.r) * (r + o.r)) {
                return c.x < o.c.x;
            }
            if(c.y < o.c.y) return true;
            return (c - o.c).dist2() <= (o.r - r) * (o.r - r);
        }
        else {
            if(c.y == o.c.y && (c - o.c).dist2() == (r + o.r) * (r + o.r)) {
                return c.x < o.c.x;
            }
            if(o.c.y < c.y) return false;
            return (c - o.c).dist2() > (o.r - r) * (o.r - r);
        }
    }
};

struct tangent_pt {
    pt q;
    ll d;
    double x, y;

    tangent_pt(pt p1, pt p2, ll dist, ll r) {
        d = dist;
        q = p1 * (d - r) + p2 * r;
        x = q.x / (double) d;
        y = q.y / (double) d;
    }

    bool operator<(tangent_pt p) const {
        __int128_t x1 = q.x * (__int128_t)p.d, x2 = p.q.x * (__int128_t)d;
        __int128_t y1 = q.y * (__int128_t)p.d, y2 = p.q.y * (__int128_t)d;
        return tie(x1, y1) < tie(x2, y2);
    }
};

void solve() {
    int n; cin >> n;
    vector<array<ll, 3>> circles(n);
    for(auto &[x, y, r]: circles)
        cin >> x >> y >> r;
        
    vector<array<ll, 3>> events;
    rep(i, 0, n) {
        auto [x, y, r] = circles[i];
        events.push_back({x - r, false, i});
        events.push_back({x + r, true, i});
    }

    sort(all(events));

    map<tangent_pt, vii> tangents;
    rep(iter, 0, 2) {
        set<upper_circle> s;
        for(auto [_, rem, idx]: events) {
            auto [x, y, r] = circles[idx];

            optional<set<upper_circle>::iterator> prv = nullopt, nxt = nullopt;
            if(!rem) {
                auto it = s.emplace(x, y, r, idx).first;
                if(it != s.begin()) prv = prev(it);
                if(next(it) != s.end()) nxt = next(it);
            }
            else {
                auto it = s.erase(s.find(upper_circle(x, y, r, idx)));
                if(it != s.begin()) prv = prev(it);
                if(it != s.end()) nxt = it; 
            }

            for(auto it: {prv, nxt}) {
                if(it == nullopt) continue;
                auto oc = *(*it);
                bool extrn = (oc.c - pt(x, y)).dist2() == (r + oc.r) * (r + oc.r);
                bool intrn = (oc.c - pt(x, y)).dist2() == (r - oc.r) * (r - oc.r);
                if(extrn || intrn) {
                    pt p1 = oc.c, p2 = pt(x, y);
                    if(iter == 1) p1.y *= -1, p2.y *= -1;
                    ll d, rad;
                    if(extrn) d = r + oc.r, rad = oc.r;
                    else {
                        d = abs(r - oc.r);
                        if(oc.r > r) rad = oc.r;
                        else rad = r, swap(p1, p2);
                    }
                    tangent_pt tp(p1, p2, d, rad);
                    int i = idx, j = oc.idx;
                    if(i > j) swap(i, j);
                    tangents[tp].emplace_back(i, j);
                }
            }
        }

        for(auto &[x, y, r]: circles)
            y *= -1;
    }
    
    ll res = 0;
    vvi adj(n);
    vector<ll> dp(n, -1);
    vi in_deg(n);
    for(auto [_, v]: tangents) {
        sort(all(v));
        v.erase(unique(all(v)), end(v));
        
        for(auto [u, v]: v) {
            auto [x1, y1, r1] = circles[u];
            auto [x2, y2, r2] = circles[v];

            if((pt(x1, y1) - pt(x2, y2)).dist2() == (r1 + r2) * (r1 + r2))
                continue;

            if(circles[u][2] < circles[v][2])
                swap(u, v);
            adj[u].push_back(v);
            in_deg[v]++;
        }

        auto dfs = [&](int cur, auto &dfs) -> ll {
            if(dp[cur] != -1) return dp[cur];
            dp[cur] = 1;
            for(int nxt: adj[cur])
                dp[cur] += dfs(nxt, dfs); 
            return dp[cur];
        };

        vector<ll> cnt;
        for(auto [u, v]: v) {
            if(in_deg[u] == 0) {
                cnt.push_back(dfs(u, dfs));
            }
            if(in_deg[v] == 0) {
                cnt.push_back(dfs(v, dfs));
            }
        }

        if(sz(cnt) < 2) continue;
        res += cnt[0] * cnt[1];
    }

    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}