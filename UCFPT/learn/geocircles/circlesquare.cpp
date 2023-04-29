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
vector<P> circleLine(P c, ld r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	ld s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}
using P = Point<ld>;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P c, ld r, vector<P> ps) {
	auto tri = [&](P p, P q) {
		auto r2 = r * r / 2;
		P d = q - p;
		auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
		auto det = a * a - b;
		if (det <= 0) return arg(p, q) * r2;
		auto s = max(ld(0), -a-sqrt(det)), t = min(ld(1), -a+sqrt(det));
		if (t < 0 || 1 <= s) return arg(p, q) * r2;
		P u = p + d * s, v = p + d * t;
		return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
	};
	auto sum = 0.0;
	rep(i,0,sz(ps))
		sum += tri(ps[i] - c, ps[(i + 1) % sz(ps)] - c);
	return sum;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ld x, y, r; cin >> x >> y >> r;
    ld tx, ty, s; cin >> tx >> ty >> s;
    ld tx1 = tx + s, ty1 = ty + s;
    P bl(tx, ty), br(tx1, ty), tl(tx, ty1), tr(tx1, ty1);
    vector<P> ps = {bl, br, tr, tl};
    int intpoints = 0;
    P c(x, y);
    auto numint = [&](P a, P b)->int{
        int ans = 0;
        for(auto &p : circleLine(c, r, a, b)){
            if(p.x <= tx1 && p.x >= tx && p.y <= ty1 && p.y >= ty && !(p == b)) ans++;
        }
        // cout << a << " " << b << " " << ans << nL;
        // if((a - c).dist2() < r * r) ans += 2;
        return ans;
    };
    intpoints += numint(br, bl) + numint(bl, tl) + numint(tl, tr) + numint(tr, br);
    // if(intpoints > 1) cout << 2 << nL;
    ld area = circlePoly(c, r, ps);
        ld eps = 1e-9;
    if(intpoints == 1 && area <= eps) cout << 1 << nL;
    else if(area > eps){
        cout << 2 << nL;
    }
    else{
        // if(area > eps) cout << 2 << nL;
        cout << 0 << nL;
    }
    // else cout << 0 << nL;

    // cout <<  << nL;
    
    return 0;
}