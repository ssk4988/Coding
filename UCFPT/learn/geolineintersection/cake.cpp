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
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
using P = Point<ll>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n; int y; cin >> y;
        vector<P> v(n);
        vector<ld> p(2);
        rep(i, 0, n){
            cin >> v[i].x >> v[i].y;
        }
        vector<ld> lx;
        rep(i, 0, n){
            int i1 = (i + 1) % n;
            if(v[i].y >= y && v[i1].y >= y){
                p[1] += (v[i1] - v[i]).dist();
            }
            else if(v[i].y <= y && v[i1].y <= y){
                p[0] += (v[i1] - v[i]).dist();
            }
            else if(v[i].y >= y && v[i1].y <= y){
                Point<ld> inter(v[i1].x - v[i].x, v[i1].y - v[i].y);
                inter = Point<ld>(v[i].x, v[i].y) + inter * fabs(v[i].y - y) / fabs(inter.y);
                lx.pb(inter.x);
                p[1] += (Point<ld>(v[i].x, v[i].y) - inter).dist();
                p[0] += (Point<ld>(v[i1].x, v[i1].y) - inter).dist();
            }
            else{
                Point<ld> inter(v[i1].x - v[i].x, v[i1].y - v[i].y);
                inter = Point<ld>(v[i].x, v[i].y) + inter * fabs(v[i].y - y) / fabs(inter.y);
                lx.pb(inter.x);
                p[1] += (Point<ld>(v[i1].x, v[i1].y) - inter).dist();
                p[0] += (Point<ld>(v[i].x, v[i].y) - inter).dist();
            }
        }
        p[0] += fabs(lx[0] - lx[1]);
        p[1] += fabs(lx[0] - lx[1]);
        if(p[1] < p[0]) swap(p[1], p[0]);
        cout << "Case #" << (cn + 1) << ": " << fixed << setprecision(3) << p[0] << " " << p[1] << nL << nL;
    }
    
    return 0;
}