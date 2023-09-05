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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, r; cin >> n >> m >> r;
    vi freq(1 << m);
    using P = Point<ll>;
    vector<P> ps(n);
    rep(i, 0, n){
        cin >> ps[i].x >> ps[i].y;
    }
    using a3 = array<ll, 3>;
    vector<a3> lines(m);
    rep(i, 0, m){
        cin >> lines[i][0] >> lines[i][1] >> lines[i][2];
        // lines[i][2] *= -1;
    }
    rep(i, 0, n){
        int bm = 0;
        rep(j, 0, m){
            bool onside = false;
            // if(lines[j][1] == 0){
            //     onside = lines[j][0] * ps[i].x > lines[j][2];
            // }
            // else{
                ll val = lines[j][0] * ps[i].x + lines[j][1] * ps[i].y + lines[j][2];
                assert(val != 0);
                onside = val > 0;
            // }
            if(onside) bm |= 1 << j;
        }
        freq[bm]++;
        cout << i << " " << bm << nL;
    }
    bool works = true;
    rep(i, 0, 1 << m){
        if(freq[i] != 1) works = false;
    }
    cout << (works ? "yes" : "no") << nL;
    
    return 0;
}
