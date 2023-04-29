#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
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
	ld dist() const { return sqrtl((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)); }
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


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ld l1, l2; cin >> l1 >> l2;
        ld pi = acosl(-1);
        ld a1 = atanl(l1 / l2) / 2, a2 = pi / 4, a3 = atanl(l1 / l2);
        P sl(1, 0); sl = sl.rotate(-a1);
        P sl2(1, 0); sl2 = sl2.rotate(a2);
        P rc(l2, 0), o(0, 0), tc(0, l1);
        P slp = rc - sl, o1 = o + sl2;
        auto[cnt, incenter] = lineInter(rc, slp, o, o1);
        ld totarea = l1 * l2 / 2;
        ld curradius = incenter.y;
        ld curarea = pi * curradius * curradius;
        P curpoint = incenter + sl * curradius;
        // P rl = (rc - tc).unit(), rl1(-1, 0);
        ld eps = 1e-15;
        while(a3 / 2 * (curpoint - rc).dist2() * 100000000.0 > totarea){
            ld lo = 0, hi = 100000;
            while(fabs(hi - lo) > eps){
                ld mid = (lo + hi) / 2;
                // P newpoint = curpoint + sl * mid;
                ld newy = curpoint.y + sl.y * mid;
                if(newy <= mid)hi = mid;
                else lo = mid;
            }
            curradius = lo;
            curpoint = curpoint + sl * curradius * 2;
            curarea += pi * curradius * curradius;
            // cout << curarea << " " << curradius << " " << curpoint << nL;
        }
        cout << "Case #" << (cn + 1) << ": " << fixed << setprecision(4) << (curarea / totarea) << nL << nL;
        
    }
    
    return 0;
}