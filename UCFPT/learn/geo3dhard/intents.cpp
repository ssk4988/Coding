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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
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
#define int long long
using P = Point<int>;
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    n--;
    vector<P> p(n);
    rep(i, 0, n) {
        cin >> p[i].x >> p[i].y;
    }
    sort(all(p), [&](P a, P b) {
        int side0 = (a.y > 0 || (a.y == 0 && a.x > 0));
        int side1 = (b.y > 0 || (b.y == 0 && b.x > 0));
        if(side0 != side1) return side0 < side1;
        return a.cross(b) > 0;
    });
    map<P, int> mult;
    rep(i, 0, n) {
        int area = p[i].cross(p[(i+1)%n]);
        mult[P(0, 0)] += area;
        mult[p[i]] += area;
        mult[p[(i+1)%n]] += area;
    }
    vi res;
    for(auto [key, val] : mult) {
        res.push_back(val);
    }
    vi h(n+1);
    rep(i, 0, n+1) cin >> h[i];
    sort(all(res));
    sort(all(h));
    int ans = 0;
    rep(i, 0, sz(h)) ans += h[i] * res[i];
    cout << fixed << setprecision(2) << ans / 6.0 << "\n";

    
    return 0;
}
