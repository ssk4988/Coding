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
	ld dist() const { return sqrt((ld)dist2()); }
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

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
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

using P = Point<ld>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int as; cin >> as;
    vector<P> a(as);
    rep(i, 0, as){
        cin >> a[i].x >> a[i].y;
    }
    reverse(all(a));
    int bs; cin >> bs;
    vector<P> b(bs);
    rep(i, 0, bs){
        cin >> b[i].x >> b[i].y;
    }
    reverse(all(b));
    vi prv(bs), nxt(bs);
    rep(i, 0, bs){
        prv[i] = (i + bs - 1) % bs;
        nxt[i] = (i+1)%bs;
    }
    vector<vector<ld>> dists(bs, vector<ld>(2));
    rep(i, 0, bs){
        // cout << i << endl;
        rep(j, 0, 2){
            int other = j ? (nxt[i]) : (i - 1 + bs) % bs;
            P dir = (b[i] - b[other]).unit();
            ld lo = 0, hi = 1e9;
            rep(_, 0, 100){
                ld mid = (lo + hi) / 2;
                P p = b[i] + dir * mid;
                if (inHull(a, p)) {
                    lo = mid;
                } else hi = mid;
            }
            dists[i][j] = lo;
        }
    }
    // cout << "got here" << endl;
    vector<vd> dp(bs, vd(bs, -1));
    auto go = [&](int l, int r, auto &&go) -> ld {
        ld &ans = dp[l][r];
        if(ans != -1) return ans;
        if(l == r) return ans = 0;
        ans = 1e18;
        for(int i = l; i != r; i = nxt[i]) {
            ld cur = go(l, i, go) + go(nxt[i], r, go) + (b[nxt[i]] - b[i]).dist();
            if(i != l) 
            {
                auto [cnt, inter] = lineInter(b[i], b[nxt[i]], b[prv[l]], b[l]);
                ld d = dists[i][1];
                if(cnt == 1 && (b[nxt[i]] - b[i]).dot(inter - b[i]) < 0) {
                    d = min(d, (inter - b[i]).dist());
                }
                cur += d;
            }
            if((i + 1)%bs != r) 
            {
                auto [cnt, inter] = lineInter(b[i], b[nxt[i]], b[r], b[nxt[r]]);
                ld d = dists[nxt[i]][0];
                if(cnt == 1 && (b[i] - b[nxt[i]]).dot(inter - b[nxt[i]]) < 0) {
                    d = min(d, (inter - b[nxt[i]]).dist());
                }
                cur += d;
            }
            ans = min(ans, cur);
        }
        return ans;
    };
    ld ans = 1e18;
    rep(i, 0, bs){
        int j = nxt[i];
        ld cur = go(j, i, go) + (b[j] - b[i]).dist() + dists[i][1] + dists[j][0];

        ans = min(ans, cur);
    }
    cout << fixed << setprecision(8) << ans << "\n";


    return 0;
}
