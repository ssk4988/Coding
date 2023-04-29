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

typedef Point<ld> P;
bool circleInter(P a,P b,ld r1,ld r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	ld d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<ld> cs(3);
    rep(i, 0, 3) cin >> cs[i];
    sort(all(cs));
    ld lo = 0, hi = cs[0] + cs[1];
    ld eps = 1e-9;
    while(fabs(hi - lo) > eps){
        ld mid = (lo + hi) / 2;
        P a(0, 0), b(mid, 0), c(mid / 2, mid / 2 * sqrtl(3));
        pair<P, P> ints;
        circleInter(a, b, cs[0], cs[1], &ints);
		if((ints.f - c).dist() <= cs[2] || (ints.s - c).dist() <= cs[2]){
			lo = mid;
		}
		else{
			hi = mid;
		}
    }
	P a(0, 0), b(lo, 0), c(lo / 2, lo / 2 * sqrtl(3));
	pair<P, P> ints;
	circleInter(a, b, cs[0], cs[1], &ints);
	eps = 1e-3;
	if(fabs((ints.f - c).dist() - cs[2]) <= eps || fabs((ints.s - c).dist() - cs[2]) <= eps){
	// if(((ints.f - c).dist() <= cs[2] && ints.f.y <= c.y && ints.f.y >= 0) || ((ints.s - c).dist() <= cs[2] && ints.s.y <= c.y && ints.s.y >= 0)){
		cout << fixed << setprecision(3) << (lo * lo * sqrtl(3)) / 4 << nL;
	}
	else{
		cout << "-1.000\n";
	}
    
    return 0;
}