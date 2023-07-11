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
};

template<class P>
int lineIntersection(const P& s1, const P& e1, const P& s2,
		const P& e2, P& r) {
	if ((e1-s1).cross(e2-s2)) { //if not parallell
		r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
		return 1;
	} else
		return -((e1-s1).cross(s2-s1)==0 || s2==e2);
}

#define eps 1e-8
typedef Point<ld> P;

struct Line {
	P P1, P2;
	// Right hand side of the ray P1 -> P2
	explicit Line(P a = P(), P b = P()) : P1(a), P2(b) {};
	P intpo(Line y) {
		P r;
		assert(lineIntersection(P1, P2, y.P1, y.P2, r) == 1);
		return r;
	}
	P dir() {
		return P2 - P1;
	}
	bool contains(P x) {
		return (P2 - P1).cross(x - P1) < eps;
	}
	bool out(P x) {
		return !contains(x);
	}
}; 

template<class T>
bool mycmp(Point<T> a, Point<T> b) {
	// return atan2(a.y, a.x) < atan2(b.y, b.x);
	if (a.x * b.x < 0)	return a.x < 0;
	if (abs(a.x) < eps) {
		if (abs(b.x) < eps) 	return a.y > 0 && b.y < 0;
		if (b.x < 0)	return a.y > 0;
		if (b.x > 0)	return true;
	}
	if (abs(b.x) < eps) {
		if (a.x < 0)	return b.y < 0;
		if (a.x > 0)	return false;
	}
	return a.cross(b) > 0;
}

bool cmp(Line a, Line b) {
	return mycmp(a.dir(), b.dir());
}

vector<P> Intersection_Area(vector <Line> b) {
	sort(b.begin(), b.end(), cmp);
	int n = b.size();
	int q = 1, h = 0, i;
	vector <Line> c(b.size() + 10);
	for (i = 0; i < n; i++) {
		while (q < h && b[i].out(c[h].intpo(c[h - 1])))	h--;
		while (q < h && b[i].out(c[q].intpo(c[q + 1])))	q++;
		c[++h] = b[i];
		if (q < h && abs(c[h].dir().cross(c[h - 1].dir())) < eps) {
			if (c[h].dir().dot(c[h - 1].dir()) > 0) {
				h--;
				if (b[i].out(c[h].P1))	c[h] = b[i];
			}else {
				// The area is either 0 or infinite.
				// If you have a bounding box, then the area is definitely 0. 
				return {};
			}
		}
	}
	while (q < h - 1 && c[q].out(c[h].intpo(c[h - 1])))	h--;
	while (q < h - 1 && c[h].out(c[q].intpo(c[q + 1])))	q++;
	// Intersection is empty. This is sometimes different from the case when
	// the intersection area is 0. 
	if (h - q <= 1)	return {};
	c[h + 1] = c[q];
	vector <P> s;
	for (i = q; i <= h; i++)	s.push_back(c[i].intpo(c[i + 1]));
	// s.push_back(s[0]);
	// ld ans = 0;
	// for (i = 0; i < (int) s.size() - 1; i++)	ans += s[i].cross(s[i + 1]);
	// return ans / 2;
    return s;
}

array<P, 2> hullDiameter(vector<P> S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<ld, array<P, 2>> res({0, {S[0], S[0]}});
	rep(i,0,j)
		for (;; j = (j + 1) % n) {
            // pair<ld, array<P, 2>> test = {(S[i] - S[j]).dist2(), {S[i], S[j]}};
            // if(test > res){
            //     res = test;
            // }
            // else break;
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll d; cin >> n >> d;
    vector<P> p(n);
    rep(i, 0, n){
        cin >> p[i].x >> p[i].y;
    }
    // reverse(all(p));
    ld lo = 0, hi = sqrtl(3e14);
    const ld epsans = 1e-9;
    while(fabs(hi - lo) > epsans){
        ld mid = (lo + hi) / 2;
        vector<Line> hps, ls;
        rep(i, 0, n){
            P p1 = p[i], p2 = p[(i + 1) % n];
            Line l(p1, p2);
            ls.pb(Line(l));
            P dir = l.dir().unit().rotate(-acosl(-1)/2);
            l.P1 = l.P1 + dir * mid;
            l.P2 = l.P2 + dir * mid;
            hps.pb(l);
            // cout << dir.x << " " << dir.y << nL;
        }
        vector<P> hpi = Intersection_Area(hps);
        if(sz(hpi) == 0){
            hi = mid;
            continue;
        }
        // reverse(all(hpi));
        array<P, 2> diam = hullDiameter(hpi);
        if((diam[0] - diam[1]).dist() >= d) lo = mid;
        else hi = mid;
    }
    cout << fixed << setprecision(8) << lo << "\n";
    return 0;
}
