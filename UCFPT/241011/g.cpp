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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
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
	ll cross(P p) const { return ll(x)*p.y - ll(y)*p.x; }
	ll cross(P a, P b) const { return (a-*this).cross(b-*this); }
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

using P = Point<int>;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	// sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P>& poly, P dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
array<int, 2> lineHull(P a, P b, vector<P>& poly) {
	int endA = extrVertex(poly, (a - b).perp());
	int endB = extrVertex(poly, (b - a).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	rep(i,0,2) {
		int lo = endB, hi = endA, n = sz(poly);
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}

bool aboveLine(ll x1, ll y1, ll x2, ll y2, ll x, ll y) {
    return x1 <= x && x <= x2 && (y2 - y1) * (x - x1) <= (y - y1) * (x2 - x1);
}

const int N = 800050, Q = 300050;
P pts[N];
array<int, 4> qs[Q];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    // unordered_map<int, pii> xm;
    vii ords(n);
    rep(i, 0, n){
        cin >> pts[i].x >> pts[i].y;
        // xm[pts[i].x] = {i, pts[i].y};
        ords[i] = {pts[i].x, i};
    }
    sort(all(ords));
    sort(begin(pts), begin(pts) + n);
    int q; cin >> q;
    // CASE OUT DENEGERATE LINES
    vi res(q, -1);
    rep(i, 0, q){
        rep(j, 0, 4) cin >> qs[i][j];
        if(qs[i][0] > qs[i][2]){
            swap(qs[i][0], qs[i][2]);
            swap(qs[i][1], qs[i][3]);
        }
        // if(qs[i][0] == qs[i][2] && xm.count(qs[i][0]) && xm[qs[i][0]].s >= min(qs[i][1], qs[i][3])) res[i] = xm[qs[i][0]].f;
    }
    
    queue<tuple<int, int, vi>> qu;
    vi idxs(q); iota(all(idxs), 0);
    qu.push(make_tuple(0, n, idxs));
    while(sz(qu)) {
        auto [L, R, lines] = qu.front(); qu.pop();
        if(R-L == 1) {
            int x = pts[L].x, y = pts[L].y;
            for(auto idx : lines) {
                auto [x1, y1, x2, y2] = qs[idx];
                if(x < x1 || x > x2) continue;
                if(res[idx] == -1 && aboveLine(x1, y1, x2, y2, x, y)) {
                    res[idx] = x;
                }
            }
            continue;
        }
        int M = L + (R-L) / 2;
        vi left, right;
        vector<P> hull;
        hull.pb(P(pts[L].x, 0));
        rep(i, L, R-1) hull.pb(pts[i]);
        hull.push_back(P(pts[R-1].x, 0));
        hull.pb(pts[R-1]);
        hull = convexHull(hull);
        for(auto idx : lines) {
            auto [x1, y1, x2, y2] = qs[idx];
            if(x1 == x2) continue;
            if(pts[R-1].x < x1 || pts[L].x > x2) continue;
            if(x1 <= pts[L].x && pts[R-1].x <= x2) {
                auto [i1, i2] = lineHull(P(x1, y1), P(x2, y2), hull);
                for(int i : {i1, i2}) {
                    if(i == -1) continue;
                    if(res[idx] == -1 && aboveLine(x1, y1, x2, y2, hull[i].x, hull[i].y)) res[idx] = hull[i].x;
                    if(res[idx] == -1 && aboveLine(x1, y1, x2, y2, hull[(i+1)%sz(hull)].x, hull[(i+1)%sz(hull)].y)) res[idx] = hull[(i+1)%sz(hull)].x;
                }
                continue;
            }
            if(!(pts[M-1].x < x1 || pts[L].x > x2)) left.pb(idx);
            if(!(pts[R-1].x < x1 || pts[M].x > x2)) right.pb(idx);
        }
        qu.push(make_tuple(L, M, move(left))), qu.push(make_tuple(M, R, move(right)));
    }
    rep(i, 0, q){
        if(qs[i][0] == qs[i][2]) {
            auto it = lower_bound(all(ords), pii{qs[i][0], -1});
            if(it != end(ords)) {
                auto [x, idx] = *it;
                if(x == qs[i][0] && pts[idx].y >= min(qs[i][1], qs[i][3])) {
                    res[i] = idx;
                }
            }
        } else if(res[i] != -1) {
            auto it = lower_bound(all(ords), pii{res[i], -1});
            if(it != end(ords)) {
                auto [x, idx] = *it;
                if(x == res[i]) {
                    res[i] = idx;
                }
            }
        }
        if(res[i] != -1) cout << res[i]+1 << "\n";
        else cout << res[i] << "\n";
    }
    
    return 0;
}
