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

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int minRotation(vi s) {
	int a=0, N=sz(s);
    rep(i, 0, N) s.pb(s[i]);
	rep(b,0,N) rep(k,0,N) {
		if (a+k == b || s[a+k] < s[b+k]) {b += max(0, k-1); break;}
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<P> a(n), b(m);
    rep(i, 0, n){
        cin >> a[i].x >> a[i].y;
    }
    rep(i, 0, m){
        cin >> b[i].x >> b[i].y;
    }
    a = convexHull(a);
    b = convexHull(b);
    map<ll, int> szhsh;
    map<tuple<int, int, ll>, int> anghsh;
    n = sz(a), m = sz(b);
    vi aseq, bseq;
    rep(i, 0, n){
        // cout << a[i].x << "," << a[i].y << "\n";
        P dif = a[(i + 1) % n] - a[i], pdif = a[i] - a[(i - 1 + n) % n];
        ll len = dif.dist2(), plen = pdif.dist2();
        if(!szhsh.count(len)) szhsh[len] = sz(szhsh);
        if(!szhsh.count(plen)) szhsh[plen] = sz(szhsh);
        tuple<int, int, ll> frac = {szhsh[plen], szhsh[len], dif.dot(pdif)};
        if(!anghsh.count(frac)) anghsh[frac] = sz(anghsh);
        aseq.pb(anghsh[frac]);
    }
    // cout << "b:\n";
    rep(i, 0, m){
        // cout << b[i].x << "," << b[i].y << "\n";
        P dif = b[(i + 1) % m] - b[i], pdif = b[i] - b[(i - 1 + m) % m];
        ll len = dif.dist2(), plen = pdif.dist2();
        if(!szhsh.count(len)) szhsh[len] = sz(szhsh);
        if(!szhsh.count(plen)) szhsh[plen] = sz(szhsh);
        tuple<int, int, ll> frac = {szhsh[plen], szhsh[len], dif.dot(pdif)};
        if(!anghsh.count(frac)) anghsh[frac] = sz(anghsh);
        bseq.pb(anghsh[frac]);
    }
    // cout << sz(aseq) << "  " << sz(bseq) << "\n";
    if(sz(aseq) != sz(bseq)){
        cout << "NO\n";
        return 0;
    }
    int ar = minRotation(aseq);
    rotate(aseq.begin(), aseq.begin() + ar, aseq.end());
    int br = minRotation(bseq);
    rotate(bseq.begin(), bseq.begin() + br, bseq.end());
    cout << (aseq == bseq ? "YES" : "NO") << "\n";
    

    
    return 0;
}
