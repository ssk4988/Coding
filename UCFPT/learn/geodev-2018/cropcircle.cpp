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
	ld dist() const { return sqrtl((ld)dist2()); }
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

typedef Point<ld> P;
ld ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    int cn = 0;
    while(true){
        cin >> n;cn++;
        if(n == 0) break;
        vector<Point<int>> v(n);
        vector<P> v2(n);
        rep(i, 0, n){
            cin >> v[i].x;
            v2[i].x = v[i].x;
        }
        rep(i, 0, n){
            cin >> v[i].y;
            v2[i].y = v[i].y;
        }
        int ans = 0;
        ld eps = 1e-9;
        rep(i, 0, n){
            rep(j, i + 1, n){
                rep(k, j + 1, n){
                    if(v[i].cross(v[j], v[k]) == 0) continue;
                    P c = ccCenter(v2[i], v2[j], v2[k]);
                    ld r = ccRadius(v2[i], v2[j], v2[k]);
                    vi cc, cc2 = {i, j, k};
                    rep(l, 0, n){
                        if(fabs(r - (v2[l] - c).dist()) <= eps) cc.push_back(l);
                    }

                    assert(sz(cc) >= 3);
                    bool works = true;
                    rep(l, 0, 3){
                        if(cc[l] != cc2[l]) 
                            works = false;
                    }
                    if(works) ans++;
                }
            }
        }
        cout << "Circles for boulder set #" << cn << ": " << ans << nL;
    }
    
    return 0;
}