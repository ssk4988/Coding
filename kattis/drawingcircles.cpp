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

typedef Point<double> P;
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

const double eps = 1e-9;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl xs(n), ys(n), rs(n);
    vector<P> cs(n);
    rep(i, 0, n){
        cin >> xs[i] >> ys[i] >> rs[i];
        cs[i] = P(xs[i], ys[i]);
    }
    double ans = 0;
    rep(i, 0, n){
        bool covered = false;
        rep(j, i+1, n){
            if(rs[j] < rs[i]) continue;
            if ((xs[j] - xs[i]) * (xs[j] - xs[i]) + (ys[j] - ys[i]) * (ys[j] - ys[i]) <= (rs[j] - rs[i]) * (rs[j] - rs[i])) {
                covered = true;
                break;
            }
        }
        if(covered) continue;
        vector<pair<double, int>> events;
        rep(j, i+1, n){
            pair<P, P> inter;
            bool has_inter = circleInter(cs[i], cs[j], rs[i], rs[j], &inter);
            if(!has_inter) continue;
            P ref = cs[j] - cs[i];
            ref = ref.unit() * rs[i] * 2;
            ref = ref + cs[i];
            // cout << ref << " " << inter.f << " " << inter.s << " ";
            if (ref.cross(inter.f, inter.s) > 0) swap(inter.f, inter.s);
            // cout << inter.f << " " << inter.s << endl;
            double ang1 = (inter.f - cs[i]).angle(), ang2 = (inter.s - cs[i]).angle();
            if (ang1 <= ang2) {
                events.push_back({ang1, 1});
                events.push_back({ang2, -1});
            } else {
                events.push_back({ang1, 1});
                events.push_back({acos(-1), -1});
                events.push_back({-acos(-1), 1});
                events.push_back({ang2, -1});
            }
        }
        events.push_back({-acos(-1), 0});
        events.push_back({acos(-1), 0});
        sort(all(events));
        double start = -acos(-1);
        int cnt = 0;
        for(auto [x, t] : events) {
            double dt = x - start;
            if(cnt == 0) ans += rs[i] * dt;
            start = x;
            cnt += t;
        }
    }
    cout << fixed << setprecision(9) << ans << "\n";
    
    return 0;
}
