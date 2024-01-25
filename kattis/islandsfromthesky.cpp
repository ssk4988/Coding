#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = double;
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

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}

template<class P>
bool inHull(const vector<P>& l, P p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}


using P = Point<ll>;
using Pd = Point<ld>;
Pd topd(P p){
    return Pd(p.x, p.y);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vector<P>> poly(n);
    vector<array<P, 2>> lines(m);
    vector<array<P, 2>> aux(m);
    vector<array<ll, 2>> zs(m);
    rep(i, 0, n){
        int k; cin >> k;
        poly[i] = vector<P>(k);
        rep(j, 0, k){
            cin >> poly[i][j].x >> poly[i][j].y;
        }
    }
    rep(i, 0, m){
        cin >> lines[i][0].x >> lines[i][0].y >> zs[i][0] >> lines[i][1].x >> lines[i][1].y >> zs[i][1];
    }

    vi cansee(n);
    rep(i, 0, m){
        aux[i][0] = lines[i][0] + (lines[i][1] - lines[i][0]).perp().perp().perp();
        aux[i][1] = lines[i][1] + (lines[i][0] - lines[i][1]).perp().perp().perp();
        rep(j, 0, n){
            bool in = true;
            for(P p : poly[j]){
                if(lines[i][0].cross(aux[i][0], p) < 0) in = false;
                if(lines[i][1].cross(aux[i][1], p) < 0) in = false;
            }
            if(in) cansee[j] = true;
        }
    }
    rep(i, 0, n){
        if(!cansee[i]){
            cout << "impossible\n";
            return 0;
        }
    }

    ld lo = 0, hi = 90;
    rep(_, 0, 100){
        ld mid = (lo + hi) / 2;
        cansee = vi(n);
        rep(i, 0, m){
            vector<Pd> perim;
            rep(j, 0, 2){
                ld dif = zs[i][j] * tan(mid / 180 * acosl(-1));
                Pd d = topd(aux[i][j] - lines[i][j]);
                d = d.unit() * dif;
                perim.pb(topd(lines[i][j]) - d);
                perim.pb(topd(lines[i][j]) + d);
            }
            rep(j, 0, n){
                bool in = true;
                for(P p : poly[j]){
                    if(!inHull(perim, topd(p), false)){
                        in = false;
                    }
                }
                if(in) cansee[j] = true;
            }
        }
        bool works = true;
        rep(i, 0, n){
            if(!cansee[i]) works = false;
        }
        if(works) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(10) << lo << "\n";
    return 0;
}
