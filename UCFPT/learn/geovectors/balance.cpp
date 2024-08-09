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
P lineProj(P a, P b, P p, bool refl=false) {
	P v = b - a;
	return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}

typedef Point<ld> P;
P polygonCenter(const vector<P>& v) {
	P res(0, 0); ld A = 0;
	for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
		res = res + (v[i] + v[j]) * v[j].cross(v[i]);
		A += v[j].cross(v[i]);
	}
	return res / A / 3;
}



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    cout << fixed << setprecision(2);
    rep(cn, 0, nc){
        vector<P> p(3);
        rep(i, 0, 3) cin >> p[i].x >> p[i].y;
        int best = 0;
        rep(i, 0, 3){
            if((p[best+1]-p[best]).dist2() < (p[(i+1)%3] - p[i]).dist2()) best = i;
        }
        int p1 = best, p2 = (best + 1) % 3, p3 = (best + 2) % 3;
        P midpoint = lineProj(p[p1], p[p2], p[p3]);
        if((p[p3] - p[p1]).dist2() < (p[p3] - p[p2]).dist2()) swap(p2, p1);
        ld lo = 0, hi = 1;
        rep(i,0,100){
            ld mid = (lo + hi) / 2;
            P pp2 = (midpoint - p[p1]) * mid + p[p1], pp3 = (p[p3] - p[p1]) * mid + p[p1];
            if(fabs(p[p1].cross(pp2, pp3)) * 2 < fabs(p[p1].cross(p[p2], p[p3]))){
                lo = mid;
            } else hi = mid;
        }
        // P center = polygonCenter(p);
        P proj = (midpoint - p[p1]) * lo + p[p1];
        // cout << proj << " " << center << "\n";
        cout << "Triangle #" << (cn+1) << " Balance Point: (" << proj.x << "," << proj.y << ")\n";
    }
    
    return 0;
}
