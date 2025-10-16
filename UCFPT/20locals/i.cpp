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

using ld = long double;
template<class T>
struct Point {
    T x, y;
    Point(T x=0, T y=0) : x(x), y(y) {}
    Point operator+(Point p) const  { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) const  { return Point(x - p.x, y - p.y); }
    Point operator*(T c)  const { return Point(x * c, y * c); }
    Point operator/(T c) const  { return Point(x / c, y / c); }
    T cross(Point p) const { return x * p.y - y * p.x; }
    T dot(Point p) const { return x * p.x + y * p.y; }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrtl(dist2()); };
    T cross(Point p, Point q) const {
        return (p-*this).cross(q-*this); 
    }
    Point unit() const { return *this / dist(); }
};

template<class P>
vector<P> circleLine(P c, ld r, P a, P b) {
    P ab = b-a, p = a + ab * (c-a).dot(ab) / ab.dist2();
    ld s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
    if(h2 < 0) return {};
    if(h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p-h, p+h};
}


using P = Point<ld>;

const ld eps = 1e-6;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ld xc, yc, r, l, u;
    cin >> xc >> yc >> r >> l >> u;
    int n; cin >> n;
    rep(cn, 0, n) {
        int f; cin >> f;
        ld xa, ya, h, a, so, d; cin >> xa >> ya >> h >> a >> so >> d;
        ld s = sqrtl(so * so - d * d);
        P c(xc, yc);
        ld zl, zr;
        if(d == 0) {
            if(l <= a && a <= u) {
                zl = -1;
                zr = 1e18;
            } else {
                zl = -1;
                zr = -2;
            }
        } else {
            zl = (a-u)/d, zr = (a-l)/d;
        }
        P plane(xa, ya);
        auto non = [&]() {
            cout << "Flight " << f << " is safe." << "\n";
        };
        P dir(cos(h/180*acosl(-1)), sin(h/180*acosl(-1)));
        P plane2 = plane + dir;
        vector<ld> ts;
        if(so == d) {
            if ((plane - c).dist() > r + eps) {
                ts.push_back(-1);
                ts.push_back(-2);
            } else {
                ts.push_back(-1);
                ts.push_back(1e18);
            }
        } else {
            vector<P> inter = circleLine(c, r, plane, plane2);
            if(sz(inter) == 0) {
                non();
                continue;
            }
            for(auto p : inter) {
                ts.push_back((p - plane).dot(dir) / s);
            }
            if(sz(ts) < 2) ts.push_back(ts.back());
            sort(all(ts));
        }
        ld tl = max({ld(0), ts[0], zl});
        ld tr = min(ts[1], zr);
        // cerr << fixed << setprecision(5);
        // cerr << ts[0] << " " << ts[1] << " " << zl << " " << zr << endl;
        // cerr << "dir: " << dir.x << " " << dir.y << endl;
        if(tl > tr + eps) {
            non();
            continue;
        }
        cout << fixed << setprecision(2);
        cout << "Incoming! Flight " << f << " enters at " << tl << " and exits at " << tr << ".\n";
    }


    return 0;
}
