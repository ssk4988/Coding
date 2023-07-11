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

template <class T>
int sgn(T x)
{
    return (x > 0) - (x < 0);
}
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts)
{
    if (sz(pts) <= 1)
        return pts;
    sort(all(pts));
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts)
        {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0)
                t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template <class T>
T polygonArea2(vector<Point<T>> &v)
{
    T a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }



template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

#define cmp(i, j) p.cross(h[i], h[j == n ? 0 : j]) * (R ?: -1)
template<bool R, class P> int getTangent(vector<P>& h, P p) {
	int n = sz(h), lo = 0, hi = n - 1, md;
	if (cmp(0, 1) >= R && cmp(0, n - 1) >= !R) return 0;
	while (md = (lo + hi + 1) / 2, lo < hi) {
		auto a = cmp(md, md + 1), b = cmp(md, lo);
		if (a >= R && cmp(md, md - 1) >= !R) return md;
		if (cmp(lo, lo + 1) < R)
			a < R&& b >= 0 ? lo = md : hi = md - 1;
		else a < R || b <= 0 ? lo = md : hi = md - 1;
	}
	return -1; // point strictly inside hull
}
template<class P> pi hullTangents(vector<P>& h, P p) {
	return {getTangent<0>(h, p), getTangent<1>(h, p)};
}

using P = Point<ll>;

bool inHull(const vector<P> &l, P p, bool strict = true)
{
    int a = 1, b = sz(l) - 1, r = !strict;
    if (sz(l) < 3)
        return r && onSegment(l[0], l.back(), p);
    if (sideOf(l[0], l[a], l[b]) > 0)
        swap(a, b);
    if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r)
        return false;
    while (abs(a - b) > 1)
    {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k;
    cin >> n >> k;
    vector<P> pts(n), kpts(k), opts;
    rep(i, 0, n)
    {
        cin >> pts[i].x >> pts[i].y;
        if (i < k)
            kpts[i] = pts[i];
        else
            opts.pb(pts[i]);
    }
    vector<P> curhull = convexHull(kpts);
    ll curarea = polygonArea2(curhull);
    vector<P> notinhull;
    for (P po : opts)
    {
        if (!inHull(curhull, po))
        {
            notinhull.pb(po);
        }
    }
    sort(all(notinhull), [&](const P &p1, const P &p2) -> bool
         {
    int s1 = p1.y < curhull[0].y || (p1.y == curhull[0].y && p1.x < curhull[0].x); 
    int s2 = p2.y < curhull[0].y || (p2.y == curhull[0].y && p2.x < curhull[0].x);
    if(s1 != s2) return s1 < s2;
    return curhull[0].cross(p1, p2) > 0; });
    ll ans = curarea;
    if (sz(notinhull) == 0)
    {
        cout << fixed << setprecision(1) << (ld(ans) / 2) << nL;
        return 0;
    }
    P fp = notinhull[0];
    n = sz(curhull);
    int l = -1, r = -1;
    auto nex = [&](int i) -> int
    { return (i + 1) % n; };
    auto pre = [&](int i) -> int
    { return (n + i - 1) % n; };
    vl crosses(n);
    crosses[n - 1] = curhull[n - 1].cross(curhull[0]);
    rep(i, 0, n - 1) crosses[i] = curhull[i].cross(curhull[i + 1]);
    vl prefc(crosses);
    rep(i, 1, n) prefc[i] += prefc[i - 1];
    auto rangesum = [&](int l, int r)->ll{
        if(l == r) return 0;
        assert(l < r);
        ll res = prefc[r - 1];
        if(l) res -= prefc[l - 1];
        return res;
    };
    auto getarea = [&](int l, int r)->ll{
        if(l <= r) return rangesum(l, r) + curhull[r].cross(curhull[l]);
        else{
            ll res = rangesum(0, r) + rangesum(l, n) + curhull[r].cross(curhull[l]);
            return res;
        }
    };
    for(P po : notinhull){
        pi idxs = hullTangents(curhull, po);
        ll area = getarea(idxs.f, idxs.s);
        ans = max(ans, curarea - area + po.cross(curhull[idxs.s], curhull[idxs.f]));
    }
    
    cout << fixed << setprecision(1) << (ld(ans) / 2) << nL;

    return 0;
}
