#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define double long double

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

#define sgn(x) ((x > 0) - (x < 0))

struct pt {
    ll x, y;
    pt(ll x = 0, ll y= 0): x(x), y(y) {}
    pt operator+(pt p) { return pt(x + p.x, y + p.y); }
    pt operator-(pt p) { return pt(x - p.x, y - p.y); }
    pt operator*(ll c) { return pt(x * c, y * c); }
    pt operator/(ll c) { return pt(x / c, y / c); }
    ll cross(pt p) { return x * p.y - y * p.x; }
    ll cross(pt p, pt q) { return (p-*this).cross(q-*this); }
    ll dot(pt p) { return x*p.x + y*p.y; }
    pt perp() { return pt(-y, x); }
    double dist() { return sqrtl(x*x + y*y); }
};

struct ptd {
    double x, y;
    ptd(double x = 0, double y = 0): x(x), y(y) {}
    ptd operator+(ptd p) { return ptd(x + p.x, y + p.y); }
    ptd operator-(ptd p) { return ptd(x - p.x, y - p.y); }
    ptd operator*(double c) { return ptd(x * c, y * c); }
    ptd operator/(double c) { return ptd(x / c, y / c); }
    double cross(ptd p) { return x * p.y - y * p.x; }
    double cross(ptd p, ptd q) { return (p-*this).cross(q-*this); }
    double dot(ptd p) { return x*p.x + y*p.y; }
    ptd perp() { return ptd(-y, x); }
    double dist() { return sqrtl(x*x + y*y); }
};

#define cmp(i, j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i+1, i) >= 0 && cmp(i, i-1+n) < 0
template <class P> int extrVertex(vector<P>& poly, P dir) {
    int n = sz(poly), lo = 0, hi = n;
    if(extr(0)) return 0;
    while(lo+1 < hi) {
        int m = (lo + hi) / 2;
        if(extr(m)) return m;
        int ls = cmp(lo+1, lo), ms = cmp(m+1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
    }
    return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
array<int, 2> lineHull(P a, P b, vector<P>& poly) {
    int endA = extrVertex(poly, (a-b).perp());
    int endB = extrVertex(poly, (b-a).perp());
    if(cmpL(endA) < 0 || cmpL(endB) > 0)
        return {-1, -1};
    array<int, 2> res;
    rep(i,0,2) {
        int lo = endB, hi = endA, n = sz(poly);
        while((lo+1)%n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmpL(m) == cmpL(endB) ? lo : hi)  = m;

        }
        res[i] = (lo + !cmpL(hi)) % n;
        swap(endA, endB);
    }
    if(res[0] == res[1]) return {res[0], -1};
    if(!cmpL(res[0]) && !cmpL(res[1]))
        switch((res[0] - res[1]  + sz(poly)+1)% sz(poly)) {
            case 0: return {res[0], res[0]};
            case 2: return {res[1], res[1]};
        }
    return res;
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if(d == 0) return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

#define todouble(p) (ptd(p.x, p.y))

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;
    vector<pt> small(m), large(n);
    for(auto &[x, y]: large)
        cin >> x >> y;
    for(auto &[x, y]: small)
        cin >> x >> y;

    vector<double> ssum(2*n+1);
    for(int i = 2*n-1; i >= 0; i--) {
        ssum[i] = (large[i%n] - large[(i+1)%n]).dist();
        ssum[i] += ssum[i+1];
    }

    double perim = 0;
    rep(i, 0, n)
        perim += (large[i%n] - large[(i+1)%n]).dist();

    double res = 0;
    rep(idx, 0, m) {
        pt s = small[idx], e = small[(idx+1)%m];
        auto [i, j] = lineHull(s, e, large);
        int L = i+1, R = j;
        if(L > R) R += n;
        double len = 0;
        len += ssum[L] - ssum[R];

        // cout << "FOR " << idx <<":\n";
        // cout << i << ' ' << j << '\n';
        // cout << L << ' ' << R << '\n';
        
        ptd sd(s.x, s.y), ed(e.x, e.y);
        auto [_1, p1] = lineInter(todouble(large[i]), todouble(large[(i+1)%n]), sd, ed);
        auto [_2, p2] = lineInter(todouble(large[j]), todouble(large[(j+1)%n]), sd, ed);
        
        // cout << "pts: " << '\n';
        // cout << p1.x << ' ' << p1.y << '\n';
        // cout << p2.x << ' ' << p2.y << '\n';
        
        // cout << res << '\n';
        len += (todouble(large[(i+1)%n]) - p1).dist();
        // cout << res << '\n';
        len += (todouble(large[j]) - p2).dist();
        // cout << res << '\n';

        res += (s - e).dist() * len;
    }

    cout << setprecision(20) << fixed;
    cout << res / perim << '\n';

    return 0;
}

/*
4 4
0 0
3 0
3 3
0 3
1 1
2 1
2 2
1 2
FOR 0:
3 1
4 5
pts:
0 1
3 1
3
4
5
FOR 1:
0 2
1 2
pts:
2 0
2 3
8
9
10
FOR 2:
1 3
2 3
pts:
3 2
0 2
13
14
15
FOR 3:
2 0
3 4
pts:
1 3
1 0
18
19
20
*/
