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
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    int side() const { return y < 0 || (y == 0 && x < 0); }
    bool operator<(P p) const
    {
        if (side() != p.side())
            return side() < p.side();
        return cross(p) > 0;
    }
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
    T slope() const { return y / x; }
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
using P = Point<ll>;

// bool cmp(const P& x, const P& p)
// {
//     return pl{x.x, x.y} < pl{p.x, p.y};
// }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<P> pts(n);
    rep(i, 0, n)
    {
        cin >> pts[i].x >> pts[i].y;
        pts[i].x *= 2, pts[i].y *= 2;
    }
    int ans = n;
    {
        map<pl, int> frq;
        rep(i, 0, n){
            frq[{pts[i].x, pts[i].y}]++;
            rep(j, i+1, n){
                P p = (pts[i] + pts[j]) / 2;
                frq[{p.x, p.y}] += 2;
            }
        }
        for(auto [key, val] : frq){
            ans = min(ans, n - val);
        }
    }
    vector<pair<P, pi>> events;
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            if (i == j)
                continue;
            events.pb({pts[j] - pts[i], {i, j}});
            events.pb({(pts[j] - pts[i]).perp().perp().perp(), {-1, -1}});
        }
    }
    // cout << ans << "\n";
    sort(all(events));
    vi order(n);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) {return pts[a].y < pts[b].y; });
    vi rev(n);
    rep(i, 0, n){
        rev[order[i]] = i;
    }
    int start = 0;
    map<P, unordered_map<ll, int>> cnt;
    while (start < sz(events))
    {
        // cout << start << endl;
        int end = start;
        P scale = events[start].f;
        // cout << scale << endl;
        scale = scale / abs(__gcd(scale.x, scale.y));
        while (end < sz(events) && events[end].f.cross(scale) == 0)
        {
            auto [dir, ps] = events[end];
            auto [i1, i2] = ps;
            if(i1 == -1) {
                end++;
                continue;
            }
            P mid = (pts[i1] + pts[i2]) / 2;
            cnt[scale][scale.dot(mid)] += 2;
            ans = min(ans, n - cnt[scale][scale.dot(mid)]);
            end++;
        }
        start = end;
    }
    // cout << "done" << endl;
    start = 0;
    while (start < sz(events))
    {
        int end = start;
        P scale = events[start].f;
        scale = scale / abs(__gcd(scale.x, scale.y));
        P perp = scale.perp();
        auto cmp = [&](int idx, ll v) {
            return perp.dot(pts[order[idx]]) < v;
        };
        auto cmp1 = [&](int idx, ll v) {
            return perp.dot(pts[order[idx]]) > v;
        };
        while (end < sz(events) && events[end].f.cross(scale) == 0)
        {
            auto [dir, ps] = events[end];
            auto [i1, i2] = ps;
            if(i1 == -1) {end++; continue;}
            if (rev[i1] < rev[i2]){
                swap(order[rev[i1]], order[rev[i2]]);
                swap(rev[i1], rev[i2]);
            }
            end++;
        }
        for (auto [key, val] : cnt[perp])
        {
            int actual = val;
            int lb = -1;
            for(int dif = 1 << 10; dif; dif /= 2) {
                if(lb + dif < sz(order) && cmp(lb + dif, key)) lb += dif;
            }
            lb++;
            int ub = -1;
            for(int dif = 1 << 10; dif; dif /= 2) {
                if(ub + dif < sz(order) && (cmp(ub + dif, key) || !cmp1(ub + dif, key))) ub += dif;
            }
            ub++;
            // auto it1 = lower_bound(all(order), key, cmp);
            // auto it2 = upper_bound(all(order), key, cmp);
            actual += ub - lb;
            ans = min(ans, n - actual);
        }
        start = end;
    }

    cout << ans << "\n";

    return 0;
}
