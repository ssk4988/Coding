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

using P = Point<ld>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    P c; cin >> c.x >> c.y;
    P outer(0,0), inner(1500000, 1500000);
    vector<P> v(n);
    rep(i, 0, n){
        P vv; cin >> vv.x >> vv.y;
        vv = vv - c;
        v[i] = vv;
        if(outer.dist2() < vv.dist2()) outer = vv;
    }
    rep(i, 0, n){
        P dif = v[(i + 1) % n] - v[i];
        ld lo = 0, hi = 1;
        rep(j, 0, 200){
            ld m3 = (hi - lo) / 3;
            ld m1 = lo + m3, m2 = hi - m3;
            P p1 = v[i] + dif * m1, p2 = v[i] + dif * m2;
            if(p1.dist2() > p2.dist2()){
                lo = m1;
            } else hi = m2;
        }
        P vv = v[i] + dif * lo;
        if(inner.dist() > vv.dist()) inner = vv;
    }
    cout << fixed << setprecision(8) << (acosl(-1) * (outer.dist2() - inner.dist2())) << "\n";
    
    return 0;
}
