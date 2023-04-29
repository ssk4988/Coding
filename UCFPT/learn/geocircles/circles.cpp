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
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

const ld PI = 3.1415926535898L;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        P prevcenter; 
        ld prevradius;
        ld area = 0;
        rep(i, 0, n){
            P center; cin >> center.x >> center.y; ld radius; cin >> radius;
            area += acos(-1) * radius * radius;
            // if(i == 0) continue;
            pair<P, P> inter;
            if(i > 0 && circleInter(prevcenter, center, prevradius, radius, &inter)){
                ld angle1 = acos(((inter.f - prevcenter).dist2() - (center - prevcenter).dist2() - (inter.f - center).dist2()) / -2 / (center - prevcenter).dist() / (inter.f - center).dist());
                ld angle2 = acos(((inter.s - prevcenter).dist2() - (center - prevcenter).dist2() - (inter.s - center).dist2()) / -2 / (center - prevcenter).dist() / (inter.s - center).dist());
                ld anglesum = angle1 + angle2;
                ld overlap = (acos(-1) * radius * radius * anglesum / 2 / acos(-1) - radius * radius * sin(anglesum) / 2);
                area -= overlap;
                swap(prevcenter, center);
                swap(prevradius, radius);
                angle1 = acos(((inter.f - prevcenter).dist2() - (center - prevcenter).dist2() - (inter.f - center).dist2()) / -2 / (center - prevcenter).dist() / (inter.f - center).dist());
                angle2 = acos(((inter.s - prevcenter).dist2() - (center - prevcenter).dist2() - (inter.s - center).dist2()) / -2 / (center - prevcenter).dist() / (inter.s - center).dist());
                anglesum = angle1 + angle2;
                overlap = (acos(-1) * radius * radius * anglesum / 2 / acos(-1) - radius * radius * sin(anglesum) / 2);
                area -= overlap;
                swap(prevcenter, center);
                swap(prevradius, radius);
            }
            prevcenter = center;
            prevradius = radius;
        }
        cout << "Set #" << (cn + 1) << ": " << fixed << setprecision(2) << area << nL;
        cout << nL;
    }
    
    return 0;
}