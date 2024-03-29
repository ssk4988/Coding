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

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}


using P = Point<ll>;
pair<bool, P> intSegInter(P a, P b, P c, P d) {
    
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0){
        P cur = a * ob - b * oa;
        if(abs(cur.x) % abs(ob - oa) == 0 && abs(cur.y) % abs(ob - oa) == 0)
		    return {true, (a * ob - b * oa) / (ob - oa)};
    }
	if (onSegment(c, d, a)) return {true, a};
	if (onSegment(c, d, b)) return {true, b};
	if (onSegment(a, b, c)) return {true, c};
	if (onSegment(a, b, d)) return {true, d};
	return {false, Point<ll>(0, 0)};
}
using Pd = Point<double>;
Pd topd(P p) {
    return Pd(p.x, p.y);
}



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<pair<P, P>> lines(n);
    ll ans = 0;
    rep(i, 0, n){
        cin >> lines[i].f.x >> lines[i].f.y >> lines[i].s.x >> lines[i].s.y;
        P dif = lines[i].s - lines[i].f;
        ll g = __gcd(abs(dif.x), abs(dif.y));
        ans += g+1;
    }
    map<P, set<int>> inters;
    rep(i, 0, n){
        rep(j, i+1, n){
            auto [hasinter, inter] = intSegInter(lines[i].f, lines[i].s, lines[j].f, lines[j].s);
            if(hasinter){
                inters[inter].insert(i);
                inters[inter].insert(j);
            }
        }
    }
    for(auto [inter, ss] : inters){
        ans -= sz(ss) - 1;
    }
    cout << ans << "\n";
    
    return 0;
}
