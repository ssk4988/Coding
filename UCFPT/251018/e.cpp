#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
	P v = b - a;
	return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}
using P = Point<double>;

const double eps = 1e-6;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
    rep(i, 0, n) {
        cin >> pts[i].x >> pts[i].y;
    }
    double ans = 0;
    rep(i, 0, n) {
        int prv = (i+n-1) % n, nxt = (i+1) % n;
        P mid = (pts[prv] + pts[nxt])/2;
        if(abs(pts[i].cross(pts[prv], pts[nxt])) <= eps) continue;
        int prv2 = (i+n-2) % n, nxt2 = (i+2)%n;
        auto score = [&](P p) {
            return - (pts[i]-pts[prv]).dist() - (pts[i]-pts[nxt]).dist() + (p-pts[prv]).dist() + (p-pts[nxt]).dist();
        };
        P opt = mid + (pts[prv]-mid).perp();
        if(pts[prv2].cross(pts[prv], opt) > -eps && pts[nxt2].cross(pts[nxt], opt) < eps) {
            cerr << i << " " << score(opt) << opt << endl;
            ans = max(ans, score(opt));
            continue;
        }
        auto [cnt, inter] = lineInter(pts[prv2], pts[prv], pts[nxt2], pts[nxt]);
        assert(cnt == 1);
        auto interpolate = [&](double t) {
            P p;
            if(t <= 1) {
                p = inter * t + pts[prv] * (1-t);
            } else {
                t -= 1;
                p = pts[nxt] * t + inter * (1-t);
            }
            double rad = (pts[prv]-pts[nxt]).dist()/2;
            P c = mid + (p-mid).unit() * rad;
            if((c-mid).dist() < (p-mid).dist()) return c;
            return p;
        };
        double lo = 0, hi = 2;
        rep(_, 0, 50) {
            double mid1 = lo + (hi-lo)/3, mid2 = hi - (hi-lo)/3;
            if(score(interpolate(mid1)) < score(interpolate(mid2))) lo = mid1;
            else hi = mid2;
        }
        cerr << i << " " << score(interpolate(lo)) << interpolate(lo) << endl;
        ans = max(ans, score(interpolate(lo)));
    }
    cout << fixed << setprecision(8) << ans << "\n";

    
    return 0;
}
