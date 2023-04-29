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
		return P(x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
vector<pair<P, P>> tangents(P c1, ld r1, P c2, ld r2) {
	P d = c2 - c1;
	ld dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (ld sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

typedef Point<ld> P;
const ld eps = 1e-15;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ld p, x, y, r;
	while(true){
		cin >> n >> p >> x >> y >> r;
		P red(x, y);
		if(n == 0) break;
		vector<pair<ld, pi>> circum;
		ld pi = acosl(-1);
		rep(i, 0, n){
			ld x1, y1, r1; cin >> x1 >> y1 >> r1;
			P c(x1, y1);
			vector<pair<P, P>> tns = tangents(red, r, c, -r1);
			assert(sz(tns) == 2);
			// if(r1 < r){
			// 	pair<int, P> inter = lineInter(tns[0].f, tns[0].s, tns[1].f, tns[1].s);
			// 	assert(inter.f == 1);
			// 	if(inter.s.dist() <= p + eps) continue;
			// }
			vector<P> ts;
			for(auto &p1 : tns){
				P d = p1.s - p1.f;
				d = d / d.dist();
				ld lo = 0, hi = 1e15;
				while(fabs(hi - lo) > eps){
					ld mid = (lo + hi) /2;
					P newp = d * mid + p1.f;
					if(newp.dist() > p) hi = mid;
					else lo = mid;
				}
				ts.pb(d * lo + p1.f);
			}
			if(c.cross(ts[0], ts[1]) < 0) swap(ts[0], ts[1]);
			if(ts[0].angle() > ts[1].angle()){
				circum.pb({-pi, {1, i}});
				circum.pb({ts[1].angle(), {-1, i}});
				circum.pb({ts[0].angle(), {1, i}}); 
				circum.pb({pi, {-1, i}});
			}
			else{
				circum.pb({ts[0].angle(), {1, i}}); 
				circum.pb({ts[1].angle(), {-1, i}});
			}
		}
		// circum.pb({-pi, 0});
		circum.pb({pi, {0, -1}});
		sort(all(circum));
		ld pre = -pi;
		map<int, ld> freq;
		set<int> f2;
		// int start = 0;
		// for(auto &p : circum){
		// 	if(f2.count(p.s.s) == 0 && p.s.f == -1){
		// 		start++;
		// 	}
		// 	f2.insert(p.s.s);
		// }
		int score = 0;
		ld ans = 0;
		// int mxscore = 0, mnscore = 
		for(auto &p : circum){
			ld dif = p.f - pre;
			freq[score] += dif;
			if(score > 0) ans += dif;
			pre = p.f;
			score += p.s.f;
		}
		cout << fixed << setprecision(4) << (1 - ans / 2 / pi) << nL;

	}
    
    return 0;
}