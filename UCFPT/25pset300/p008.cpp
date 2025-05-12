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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
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

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
using P = Point<double>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, r; cin >> n >> m >> r;
    vii p(n);
    vi a(m), b(m), c(m);
    rep(i, 0, n){
        cin >> p[i].f >> p[i].s;
    }
    rep(i, 0, m){
        cin >> a[i] >> b[i] >> c[i];
    }
    int faces = m+1;
    set<int> masks;
    rep(i, 0, n){
        int mask = 0;
        auto [x, y] = p[i];
        rep(j, 0, m){
            if(a[j] * x + b[j] * y + c[j] > 0) mask |= 1 << j;
        }
        masks.insert(mask);
    }
    rep(i, 0, m){
        rep(j, i+1, m){
            if(a[i] * b[j] == a[j] * b[i]) continue;
            P si, ei, sj, ej;
            if(a[i] == 0){
                si=P(double(-c[i]) / b[i], 0), ei=P(double(-c[i] - a[i]) / b[i], 1);
            } else{
                si=P(0, double(-c[i]) / a[i]), ei=P(1, double(-c[i] - b[i]) / a[i]);
            }
            if(a[j] == 0){
                sj=P(double(-c[j]) / b[j], 0), ej=P(double(-c[j] - a[j]) / b[j], 1);
            } else{
                sj=P(0, double(-c[j]) / a[j]), ej=P(1, double(-c[j] - b[j]) / a[j]);
            }
            auto [cnt, po] = lineInter(si, ei, sj, ej);
            assert(cnt == 1);
            if(po.dist2() <= r * r) faces++;
        }
    }
    if(sz(masks) != n || faces != n) cout << "no\n";
    else cout << "yes\n";
    
    return 0;
}
