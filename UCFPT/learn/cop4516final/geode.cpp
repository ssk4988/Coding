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

template<class P> vector<P> convex_hull(vector<P> pts){
	if(sz(pts) == 1) return pts;
	vector<P> hull(sz(pts)+1);
	int k = 0, t = 2;
	rep(_, 0, 2) {
		for(P p: pts){
			while(k >= t && hull[k-2].cross(hull[k-1], p) <= 0) k--;
			hull[k++] = p;
		}
		reverse(all(pts));
		t = k+1;
	}
	hull.resize(k-1);
	return hull;
}

using P = Point<ll>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vector<P> pts(n);
        rep(i, 0, n) cin >> pts[i].x >> pts[i].y;
        stable_sort(all(pts));
        int ans = 0;

        while(sz(pts) >= 3) {
            vector<P> hull = convex_hull(pts);
			set<P> hulls(all(hull));
            vector<P> new_pts;
            for(auto p : pts) {
				if(hulls.count(p)) continue;
                new_pts.pb(p);
            }
            pts = new_pts;
            ans++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
