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

bool side(P a){
    return a.y < 0 || (a.y == 0 && a.x < 0);
}
bool cmp(P a, P b){
    if(side(a) != side(b)) return side(a) < side(b);
    return a.cross(b) > 0;
}

vector<P> minkowski(vector<vector<P>> &polys){
    vector<P> sides;
    P init(0, 0);
    for(vector<P> &poly : polys){
        int n = sz(poly);
        P mn = poly[0];
        rep(i, 0, n){
            sides.pb(poly[(i + 1)%n] - poly[i]);
            if(poly[i].y < mn.y || (poly[i].y == mn.y && poly[i].x < mn.x)) mn = poly[i];
        }
        init = init + mn;
    }
    sort(all(sides), cmp);
    vector<P> res;
    P cur = init;
    res.pb(cur);
    for(P side : sides){
        cur = cur + side;
        res.pb(cur);
    }
    if(sz(sides)) res.pop_back();
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<vector<P>> poly(n);
    vvi adj(n);
    rep(i, 0, n){
        int k; cin >> k;
        if(k == 0){
            poly[i] = vector<P>(1);
            cin >> poly[i][0].x >> poly[i][0].y;
        }
        else{
            rep(j, 0, k){
                int v; cin >> v; v--;
                adj[i].pb(v);
            }
        }
    }
    for(int i = n - 1; i >= 0; i--){
        if(sz(adj[i]) == 0) continue;
        int k = sz(adj[i]);
        vector<vector<P>> invert(k);
        rep(j, 0, k){
            invert[j] = poly[adj[i][j]];
            for(auto &p : invert[j]){
                p = p * -1;
            }
            reverse(all(invert[j]));
        }
        rep(j, 0, k){
            vector<vector<P>> comb;
            rep(l, 0, k){
                if(l == j){
                    comb.pb(poly[adj[i][l]]);
                }   
                else{
                    comb.pb(invert[l]);
                }
            }
            vector<P> res = minkowski(comb);
            poly[i].insert(poly[i].end(), all(res));
        }
        poly[i] = convexHull(poly[i]);
    }
    ll ans = 0;
    for(P p : poly[0]){
        ans = max(ans, p.dist2());
    }
    cout << ans << "\n";

    
    return 0;
}
