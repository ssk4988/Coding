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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
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


using P = Point<ld>;
using Pl = Point<ll>;
ld segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0L,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

ld eps = 1e-8;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
	vector<Pl> ptsl(n);
    rep(i, 0, n){
        cin >> ptsl[i].x >> ptsl[i].y;
		pts[i].x = ptsl[i].x;
		pts[i].y = ptsl[i].y;
    }
	auto blocks = [&](int idx, Pl dir) -> bool {
		int prv = (idx + n - 1) % n, nxt = (idx + 1) % n;
		Pl ref = ptsl[idx] + dir;
		if(ptsl[prv].cross(ptsl[idx], ptsl[nxt]) >= 0) {
			// convex
			return (ptsl[prv].cross(ptsl[idx], ref) >= 0 && ptsl[idx].cross(ptsl[nxt], ref) >= 0) ? false : true;
		}
		// concave
		return ptsl[prv].cross(ptsl[idx], ref) < 0 && ptsl[idx].cross(ptsl[nxt], ref) < 0;
	};
    ld ans = 0;
    cout << fixed << setprecision(8);
    rep(i, 0, n){
        rep(j, 0, n){
			if(i == j) continue;
			ld posdir = 1e9, negdir = -1e9;
			P dir = (pts[j] - pts[i]).unit();
			// consider segments that intersect internally
			rep(k, 0, n){
				int k1 = (k+1) % n;
				if(ptsl[i].cross(ptsl[j], ptsl[k]) == 0 || ptsl[i].cross(ptsl[j], ptsl[k1]) == 0) continue;
				auto [cnt, inter] = lineInter(pts[i], pts[j], pts[k], pts[k1]);
				if(cnt != 1) continue;
				if(segDist(pts[k], pts[k1], inter) > eps) continue;
				ld dist = dir.dot(inter - pts[i]);
				if(dist > 0) posdir = min(posdir, dist);
				else negdir = max(negdir, dist);
			}

			// consider points on polygon that intersect
			rep(k, 0, n){
				if(ptsl[i].cross(ptsl[j], ptsl[k]) != 0) continue;
				if (i == k) {
					Pl dirl = ptsl[j] - ptsl[i];
					if(blocks(i, dirl)) posdir = 0;
					if(blocks(i, dirl * -1)) negdir = 0;
					continue;
				}
				Pl dirl = ptsl[k] - ptsl[i];
				ld dist = (pts[j] - pts[i]).unit().dot(pts[k] - pts[i]);
				if(blocks(k, dirl)) {
					if(dist > 0) posdir = min(posdir, dist);
					else negdir = max(negdir, dist);
				}
			}
			// cout << i << " " << j << " " << negdir << " " << posdir << "\n";
			ans = max(ans, posdir - negdir);
        }
    }
    cout << ans << "\n";

    return 0;
}
