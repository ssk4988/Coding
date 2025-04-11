#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

#define sgn(x) (x>0)-(x<0)
template<class T>
struct Point {
    T x, y;
    explicit Point(T x=0, T y=0): x(x), y(y) {}
    Point operator+(Point o) { return Point(x+o.x, y+o.y); }
    Point operator-(Point o) { return Point(x-o.x, y-o.y); }
    Point operator*(T c) { return Point(x*c, y*c); }
    Point operator/(T c) { return Point(x*c, y*c); }
    T cross(Point o) { return x * o.y - y * o.x; }
    T cross(Point p, Point q) { return (p-(*this)).cross(q-(*this)); }
    T dot(Point o) { return x * o.x + y * o.y; }
    Point perp() { return Point(-y,x); }
    T dist2() { return x*x + y*y; }
    double dist() { return sqrt(dist2()); }
    bool operator<(const Point o) const { return pair{x, y}<pair{o.x, o.y}; }
    bool operator==(const Point o) const { return pair{x, y}==pair{o.x, o.y}; }
};
template<class T>
ostream& operator<<(ostream& os, Point<T> p) {
    return os << p.x << "," << p.y;
}

template<class P> vector<P> convex_hull(vector<P> pts) {
    if(sz(pts) == 1) return pts;
    stable_sort(all(pts));
    vector<P> hull(sz(pts)+1);
    int k = 0, t = 2;
    rep(_, 0, 2) {
        for(P p:pts) {
            while(k >= t && hull[k-2].cross(hull[k-1], p) <= 0) k--;
            hull[k++] = p;
        }
        reverse(all(pts));
        t=k+1;
    }
    hull.resize(k-1);
    return hull;
}

#define cmp(i, j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i+1, i) >= 0 && cmp(i, i-1+n) < 0
template <class P> int extrVertex(vector<P> & poly, P dir) {
    int n = sz(poly), lo = 0, hi = n;
    if(extr(0)) return 0;
    while(lo+1<hi) {
        int m = (lo+hi)/2;
        if(extr(m)) return m;
        int ls = cmp(lo+1, lo), ms = cmp(m+1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
    }
    return lo;
}

using pt = Point<ll>;
using Pd = Point<double>;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vector<pt> pts(n);
    rep(i, 0, n) cin >> pts[i].x >> pts[i].y;
    auto hull = convex_hull(pts);
    // for(auto p : hull){
    //     cerr << p << " ";
    // }
    // cerr << endl;
    rep(i, 0, q) {
        ll a, b, c; cin >> a >> b >> c;
        pt dir(a, b);
        pt pos = hull[extrVertex(hull, dir)];
        dir = dir * -1;
        pt neg = hull[extrVertex(hull, dir)];
        // cerr << pos << " " << neg << endl;
        dir = dir * -1;
        pt perp = dir.perp();
        // cerr << "perp: " << perp << endl;
        ll mag = max(abs(dir.dot(pos)+c), abs(dir.dot(neg)+c));
        cout << fixed << setprecision(8) << mag/dir.dist() << "\n";

    }

    return 0;
}
