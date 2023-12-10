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

using P = Point<ll>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
    vi dp(n, n);
    dp[0] = 1;
    rep(i, 0, n) cin >> pts[i].x >> pts[i].y;
    sort(all(pts));
    ll d; cin >> d;
    auto higher = [](P refpoint, P a, P b)-> bool {
        return refpoint.cross(b, a) <= 0;
    };
    auto lower = [](P refpoint, P a, P b)-> bool {
        return refpoint.cross(b, a) >= 0;
    };
    rep(i, 0, n){
        P lowest(pts[i].x + 1, -1e9), highest(pts[i].x + 1, 1e9);
        rep(j, i + 1, n){
            // cout << j << " can reach " << i << " when higher is " << highest.x << " " << highest.y << " and lower is " << lowest.x << " " << lowest.y << nL;
            if(higher(pts[i], lowest, pts[j]) && lower(pts[i], highest, pts[j]))
                dp[j] = min(dp[j], 1 + dp[i]);
            if(higher(pts[i], lowest, P(pts[j].x, pts[j].y - d))) lowest = P(pts[j].x, pts[j].y - d);
            if(lower(pts[i], highest, P(pts[j].x, pts[j].y + d))) highest = P(pts[j].x, pts[j].y + d);
        }
    }
    cout << dp.back() << nL;
    return 0;
}
