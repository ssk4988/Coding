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

using P = Point<ld>;

ld eps = 1e-6;

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<P> dirs(180);
    rep(i, 0, sz(dirs)){
        dirs[i] = P(1, 0).rotate(acosl(-1) * i / 180);
    }
    int n;
    while(true){
        cin >> n;
        if(n == 0) break;
        vi x(n);
        vi ang(n);
        rep(i, 0, n){
            cin >> x[i];
        }
        rep(i, 0, n) cin >> ang[i];
        vector<P> inters;
        vvi oninter;
        rep(i, 0, n){
            rep(j, i+1, n){
                int left = x[i] < x[j] ? i : j;
                int right = left == i ? j : i;
                if(ang[left] >= ang[right]) continue;
                auto [cnt, inter] = lineInter(P(x[left], 0), P(x[left], 0) + dirs[ang[left]], P(x[right], 0), P(x[right], 0) + dirs[ang[right]]);
                assert(cnt == 1);
                int idx = sz(inters);
                rep(k, 0, sz(inters)){
                    if((inters[k] - inter).dist() < eps){
                        idx = k;
                        break;
                    }
                }
                if(idx == sz(inters)){
                    inters.pb(inter);
                    oninter.pb({});
                }
                oninter[idx].pb(i);
                oninter[idx].pb(j);
            }
        }
        rep(i, 0, sz(inters)){
            sort(all(oninter[i]));
            oninter[i].erase(unique(all(oninter[i])), oninter[i].end());
        }
        vi order(sz(inters));
        iota(all(order), 0);
        sort(all(order), [&](int i, int j) -> bool { return inters[i].y < inters[j].y; });
        vi blocked(n);
        for(int i : order){
            vi left;
            for(int p : oninter[i]){
                if(!blocked[p]) left.pb(p);
            }
            sort(all(left), [&](int a, int b) -> bool {
                ld ad = fabs(x[a] - inters[i].x), bd = fabs(x[b] - inters[i].x);
                if(fabs(ad - bd) < eps) return a < b;
                return ad < bd;
            });
            for(int j = 1; j < sz(left); j++) blocked[left[j]] = true;
        }
        vi left;
        rep(i, 0, n){
            if(!blocked[i]) left.pb(i);
        }
        cout << sz(left) << "\n";
        for(int i : left) cout << i << " ";
        cout << "\n";
    }

    
    return 0;
}
