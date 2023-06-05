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

// template<class P>
// int sideOf(const P& s, const P& e, const P& p, double eps) {
// 	auto a = (e-s).cross(p-s);
// 	double l = (e-s).dist()*eps;
// 	return (a > l) - (a < -l);
// }

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

// #define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
// #define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
// template <class P> int extrVertex(vector<P>& poly, P dir) {
// 	int n = sz(poly), lo = 0, hi = n;
// 	if (extr(0)) return 0;
// 	while (lo + 1 < hi) {
// 		int m = (lo + hi) / 2;
// 		if (extr(m)) return m;
// 		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
// 		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
// 	}
// 	return lo;
// }

// #define cmpL(i) sgn(a.cross(poly[i], b))
// template <class P>
// array<int, 2> lineHull(P a, P b, vector<P>& poly) {
// 	int endA = extrVertex(poly, (a - b).perp());
// 	int endB = extrVertex(poly, (b - a).perp());
// 	if (cmpL(endA) < 0 || cmpL(endB) > 0)
// 		return {-1, -1};
// 	array<int, 2> res;
// 	rep(i,0,2) {
// 		int lo = endB, hi = endA, n = sz(poly);
// 		while ((lo + 1) % n != hi) {
// 			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
// 			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
// 		}
// 		res[i] = (lo + !cmpL(hi)) % n;
// 		swap(endA, endB);
// 	}
// 	if (res[0] == res[1]) return {res[0], -1};
// 	if (!cmpL(res[0]) && !cmpL(res[1]))
// 		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
// 			case 0: return {res[0], res[0]};
// 			case 2: return {res[1], res[1]};
// 		}
// 	return res;
// }

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
    deque<P> inter;
    ll rangearea = 0;
    int side = -1;
    for (P po : notinhull)
    {
        int side2 = po.y < curhull[0].y || (po.y == curhull[0].y && po.x < curhull[0].x);
        if (side2 != side)
        {
            inter.clear();
            l = -1, r = -1;
            rep(i, 0, n)
            {
                if (curhull[i].cross(po, curhull[nex(i)]) > 0)
                {
                    l = i, r = nex(i);
                    break;
                }
            }
            assert(l != -1);
            while (curhull[pre(l)].cross(po, curhull[l]) > 0)
                l = pre(l);
            while (curhull[r].cross(po, curhull[nex(r)]) > 0)
                r = nex(r);
            for (int i = l; true; i = (i + 1) % n)
            {
                inter.pb(curhull[i]);
                if (i == r)
                    break;
            }
            rangearea = inter.back().cross(inter.front());
            rep(i, 0, sz(inter) - 1) rangearea += inter[i].cross(inter[i + 1]);
            side = side2;
        }
        else
        {
            while (l != r && curhull[l].cross(po, curhull[nex(l)]) < 0)
            {
                rangearea -= inter.back().cross(inter.front());
                rangearea -= inter.front().cross(inter[1]);
                l = nex(l);
                inter.pop_front();
                rangearea += inter.back().cross(inter.front());
            }
            if (l == r)
            {
                inter.clear();
                int i = l;
                l = -1, r = -1;
                for(; true; i = nex(i))
                {
                    if (curhull[i].cross(po, curhull[nex(i)]) > 0)
                    {
                        l = i, r = nex(i);
                        break;
                    }
                }
                assert(l != -1);
                while (curhull[pre(l)].cross(po, curhull[l]) > 0)
                    l = pre(l);
                while (curhull[r].cross(po, curhull[nex(r)]) > 0)
                    r = nex(r);
                for (int i = l; true; i = (i + 1) % n)
                {
                    inter.pb(curhull[i]);
                    if (i == r)
                        break;
                }
                rangearea = inter.back().cross(inter.front());
                rep(i, 0, sz(inter) - 1) rangearea += inter[i].cross(inter[i + 1]);
            }
            else
            {
                while (curhull[r].cross(po, curhull[nex(r)]) > 0)
                {
                    rangearea -= inter.back().cross(inter.front());
                    r = nex(r);
                    inter.pb(curhull[r]);
                    rangearea += inter[sz(inter) - 2].cross(inter.back());
                    rangearea += inter.back().cross(inter.front());
                }
            }
        }
        assert(po.cross(inter.back(), inter.front()) > 0);
        ans = max(ans, curarea - rangearea + po.cross(inter.back(), inter.front()));
    }
    cout << fixed << setprecision(1) << (ld(ans) / 2) << nL;

    return 0;
}
