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
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
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
    ld dist() const { return sqrt((ld)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(ld a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template <class T>
T polygonArea2(vector<Point<T>> &v)
{
    T a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}
using Pl = Point<ll>;
typedef Point<ld> P;
pair<Pl, ll> polygonCenter(const vector<Pl> &v)
{
    Pl res(0, 0);
    ll A = 0;
    for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++)
    {
        res = res + (v[i] + v[j]) * v[j].cross(v[i]);
        A += v[j].cross(v[i]);
    }
    // res / A / 3
    return {res, A};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<P> pts(n);
    vector<Pl> ptsl(n);
    ll mnX = LLONG_MAX, mxX = LLONG_MIN;
    ll addX = 0;
    rep(i, 0, n)
    {
        ll x, y;
        cin >> x >> y;
        if (i == 0)
            addX = x;
        if (y == 0)
        {
            mnX = min(mnX, x);
            mxX = max(mxX, x);
        }
        ptsl[i].x = x;
        ptsl[i].y = y;
        pts[i].x = x;
        pts[i].y = y;
    }
    auto [centerl, carea] = polygonCenter(ptsl);
    P center(centerl.x, centerl.y);
    center = center / carea / 3;
    ll centerX3 = centerl.x;
    if (3 * carea * mxX < centerX3 && mxX <= addX)
    {
        // cout << center.x << " " << mxX << " ";
        cout << "unstable\n";
        return 0;
    }
    if (centerX3 < 3 * carea * mnX && addX <= mnX)
    {
        cout << "unstable\n";
        return 0;
    }
    if (3 * carea * mnX <= centerX3 && centerX3 <= 3 * carea * mxX && mnX <= addX && addX <= mxX)
    {
        cout << "0 .. inf\n";
        return 0;
    }
    ld area = fabs(polygonArea2(pts)) / 2;
    bool right = 3 * carea * addX < centerX3;
    // cout << (3 * carea * addX)  << " " << centerX3 << "\n";
    // (center.x * area + addX * w) / (w + area) == target
    //                                == target * w + target * area
    // center.x * area - target * area == (target - addX) * w
    // (center.x - target) * area / (target - addX) = w

    // inf case: center.x < addX < target
    auto calc = [&](ld target) -> ld
    { return (center.x - target) * area / (target - addX); };

    ld mn = right ? calc(mxX) : calc(mnX);
    mn = max(mn, 0.0L);
    // ld mn = lo;
    ld mx = -1;
    bool inf = false;
    if (mnX <= addX && addX <= mxX)
    {
        inf = true;
    }
    else
    {
        mx = right ? calc(mnX) : calc(mxX);
    }
    // cout << right << " " << mn << " " << mx << "\n";
    ll mnans = mn + 1e-9;
    if (inf)
        cout << mnans << " .. inf\n";
    else if (centerX3 == (right ? mnX : mxX) * 3 * carea)
    {
        cout << "unstable\n";
    }
    else
    {
        ll mxans = mx + 1 - 1e-9;
        cout << mnans << " .. " << mxans << "\n";
    }

    return 0;
}
