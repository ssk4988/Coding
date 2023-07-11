#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
// using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
// using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

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
// typedef Point<T> P<T>;

template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
	P d = c2 - c1;
	double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (double sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}
typedef Point<ld> pd;
ld eps = 1e-9;
int main(){
    cin.tie(0)->sync_with_stdio();
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ld x1, y1, r1, x2, y2, r2, x3, y3, r3;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> x3 >> y3 >> r3;
        Point<ld> c1(x1, y1), c2(x2, y2), c3(x3, y3);
        vector<pair<pd, pd>> tns = tangents(c1, r1, c2, r2);
        auto eval = [&](pair<pd, pd> &line, ld x)->ld{
            pd dx = line.s - line.f;
            ld dx1 = x - line.f.x;
            return line.f.y + (dx * dx1 / dx.x).y;
        };
        pair<pd, pd> best;
        rep(i, 0, sz(tns)){
            if(i == 0 || eval(best, x3) > eval(tns[i], x3)){
                best = tns[i];
            }
        }
        if(best.f.x > best.s.x) swap(best.f, best.s);
        ld d = (best.s - best.f).dist();
        pd dd = (best.s - best.f) / d;
        ld newy = (r3 + dd.x * best.f.y + dd.y * x3 - dd.y * best.f.x) / dd.x;
        ld curans = y3 - newy;
        if(fabs(best.f.y - best.s.y) < eps){
            cout << "Case " << (cn + 1) << ": " << fixed << setprecision(8) << curans << nL;
            continue;
        }
        if(best.f.y < best.s.y) swap(best.f, best.s);
        dd = (best.s - best.f) / d;
        ld r = (fabs((best.s - c1).dist() - r1) <= eps) ? r1 : r2;
        r += r3;
        pd p0 = pd(x3, newy);
        pd s = p0 - ((c1 - best.s).dist() < (c2 - best.s).dist() ? c1 : c2);
        ld c = s.dist2() - r * r, b = 2 * s.dot(dd), a = dd.dist2();
        ld t1 = (-b + sqrtl(b * b - 4 * a * c)) / 2 / a, t2 = (-b - sqrtl(b * b - 4 * a * c)) / 2 / a;
        pd p1 = p0 + dd * t1, p2 = p0 + dd * t2;
        // cout << a << " " << b << " " << c << " " << r << nL;
        // ld t1 = r / s.cross(dd), t2 = r / dd.cross(s);
        // cout << best.f << " " << best.s << nL;
        // cout << p1 << " " << p2<< " " << best.s << nL;
        pd finalpoint = (p1 - p0).dist() < (p2 - p0).dist() ? p1 : p2;
        curans += (finalpoint - p0).dist() / 2 / r3 / acosl(-1);
        // cout << (p1 - best.s).dist() << " " << (p2 - best.s).dist() << nL;
        cout << "Case " << (cn + 1) << ": " << fixed << setprecision(8) << curans << nL;
    }

    return 0;
}