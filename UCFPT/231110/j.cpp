#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

struct pt {
    ll x, y;
    pt(ll x = 0, ll y = 0): x(x), y(y) {}
    bool operator<(pt p) const { return tie(x, y) < tie(p.x, p.y); }
    pt operator-(pt p) { return pt(x - p.x, y - p.y); }
    pt operator+(pt p) { return pt(x + p.x, y + p.y); }
    pt operator*(ll c) { return pt(x * c, y * c); }
    pt operator/(ll c) { return pt(x / c, y / c); }
    ll dot(pt p) { return x * p.x + y * p.y; }
    ll cross(pt p) { return x * p.y - y * p.x; }
    ll cross(pt p, pt q) { return (p - *this).cross(q - *this); }
    ll mag2() { return x*x + y*y; }
    double mag() { return sqrt(mag2()); }
};

template<class P>
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s-p).dot(e-p) <= 0;
}

#define sgn(x) ((x > 0) - (x < 0))

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    if(sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if(onSegment(c, d, a)) s.insert(a);
    if(onSegment(c, d, b)) s.insert(b);
    if(onSegment(a, b, c)) s.insert(c);
    if(onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i, 0, n) {
        P q = p[(i+1) % n];
        if(onSegment(p[i], q, a)) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}

ll scan() {
    string s; cin >> s;
    s.erase(s.find('.'), 1);
    return stoll(s);
}

using event = tuple<int, int, int>;

void solve() {
    // Scan Input
    int n; cin >> n;
    vector<pt> pts(n);
    vector<ll> vals(n);
    rep(i, 0, n) {
        pts[i].x = scan();
        pts[i].y = scan();
        vals[i] = scan();
    }

    vector<pt> large(n);
    rep(i, 0, n)
        large[i] = pts[i] * 2;

    // Construct adj list
    vvi adj(n);
    rep(i, 0, n) {
        rep(j, i+1, n) {
            pt s = pts[i], e = pts[j];

            bool good = true;
            rep(k, 0, n) {
                if(k == (i - 1 + n) % n || k == i) continue;
                if(k == (j - 1 + n) % n || k == j) continue;

                if(sz(segInter(s, e, pts[k], pts[(k+1)%n])) > 0) {
                    good = false;
                    break;
                }
            }

            if(good) rep(k, 0, n) {
                if(k == i || k == j) continue;
                if(onSegment(s, e, pts[k])) {
                    good = false;
                    break;
                }
            }

            if(good && !inPolygon(large, s + e))
                adj[i].push_back(j);
        }
    }

    rep(i, 0, n-1) {
        adj[i].push_back(i+1);
    }
    adj[0].push_back(n-1);

    rep(i, 0, n) {
        sort(all(adj[i]));
        adj[i].erase(unique(all(adj[i])), adj[i].end());
    }

    // D.P.
    vector<double> dp(n, -1);
    auto calc = [&](int cur, auto &calc) -> double {
        auto &res = dp[cur];
        if(dp[cur] != -1) return dp[cur];

        dp[cur] = 0;
        // There is an imposter among us
        for(int nxt: adj[cur])
            dp[cur] = max(dp[cur], calc(nxt, calc) - (pts[cur]-pts[nxt]).mag());
        dp[cur] += vals[cur];

        return dp[cur]; 
    };

    cout << calc(0, calc) / 10000.0 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(10) << fixed;

    int t; cin >> t;
    rep(i, 0, t) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }


    return 0;
}
