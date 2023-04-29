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

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}
using P = Point<ll>;

bool cmp(P &a, P &b){
	if(a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
	vector<P> byx(n), byy;
    rep(i, 0, n){
        cin >> byx[i].x >> byx[i].y;
		byy.pb(byx[i]);
    }
	sort(all(byx));
	sort(all(byy), cmp);
	auto solve = [&](int l, int r, vector<P> &cur, auto &&solve)->ll{
		if(sz(cur) <= 3){
			ll best = (ll)9e18L;
			for(auto &p1 : cur){
				for(auto &p2 : cur) if(!(p1 == p2)) best = min(best, (p2 - p1).dist2());
			}
			return best;
		}
		vector<P> left, right, middle;
		int mid = (l + r) / 2;
		ll x = byx[mid].x;
		for(auto &p : cur){
			if(p.x == x){
				middle.pb(p);
			}
			else if(p.x < x){
				left.pb(p);
			}
			else right.pb(p);
		}
		reverse(all(right));
		for(auto &p : middle){
			if(sz(left) * 2 < sz(cur)){
				left.pb(p);
			}
			else{
				right.pb(p);
			}
		}
		reverse(all(right));
		ll d = min(solve(l, mid, left, solve), solve(mid + 1, r, right, solve));
		middle.clear();
		for(auto &p : cur){
			if((p.x - x) * (p.x - x) <= d) middle.pb(p);
		}
		rep(i, 0, sz(middle)){
			rep(j, max(0, i - 8), i){
				d = min(d, (middle[i] - middle[j]).dist2());
			}
		}
		return d;
	};
	ll ans = solve(0, n - 1, byy, solve);
	cout << ans << nL;
    
    return 0;
}