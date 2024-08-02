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
    T slope() const { return y / x; }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
using P = Point<ld>;
int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ld w; cin >> n >> w;
    vector<P> v(n), dv(n - 1);
    vd pref(n), area(n);
    priority_queue<ld, vd, greater<ld>> pq;
    rep(i, 0, n){
        cin >> v[i].x >> v[i].y;
        pq.push(v[i].x);
        if(v[i].x - w > v[0].x) pq.push(v[i].x - w);
    }
    rep(i, 0, n - 1){
        dv[i] = v[i + 1] - v[i];
        area[i] = pref[i + 1] = (v[i + 1].y + v[i].y) / 2 * (v[i + 1].x - v[i].x);
        // if(i > 0) pref[i] += pref[i - 1];
    }
    rep(i, 1, n) pref[i] += pref[i - 1];
    ld start = v[0].x;
    ld ans = 0;
    auto f = [&](int i, ld x)->ld{
        P d = v[i + 1] - v[i];
        return v[i].y + d.y * (x - v[i].x) / d.x;
    };
    auto left = [&](int i, ld x)->ld{
        if(i >= n - 1 || i < 0) return 0;
        return (x - v[i].x) * (v[i].y + f(i, x)) / 2;
    };
    auto eval = [&](int l, int r, ld x)->ld{
        ld x2 = x + w;
        ld leftsec = (r > l ? area[l] : left(l, x2)) - left(l, x);
        ld midsec = 0;
        ld rightsec = 0;
        if(r > l){
            midsec = pref[r] - pref[l + 1];
            rightsec = left(r, x2);
        }
        // cout << l << " " << r << " " << x << " is " << (leftsec + midsec + rightsec) << nL;
        return leftsec + midsec + rightsec;
    };
    ld eps = 1e-9;
    int l = 0, r = 0;
    // while(r + 1 < n && v[r + 1].x <= v[l].x + w) r++;
    set<ld> mids;
    while(!pq.empty()){
        ld x = pq.top(); pq.pop();
        while(l + 1 < n && v[l + 1].x <= x - eps) l++;
        while(r + 1 < n && v[r + 1].x <= x + w - eps) r++;
        if(l >= n - 1) break;
        ans = max(ans, eval(l, r, x));
        if(r + 1 < n){
            ld slope = dv[r].slope() - dv[l].slope();
            if(slope < 0 && f(r, x + w) >= f(l, x)){
                ld mid = v[l].x + (f(r, x + w) - f(l, x)) / -slope;
                if(!mids.count(mid) && mid > x){
                    mids.insert(mid);
                    pq.push(mid);
                }
            }
        }
    }
    cout << fixed << setprecision(8) << (ans / w) << nL;

    
    return 0;
}
