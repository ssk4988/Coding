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
    int side() const
    {
        return y < 0 || (y == 0 && x < 0);
    }
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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<P> pts(n);
    rep(i, 0, n){
        cin >> pts[i].x >> pts[i].y;
    }
    vi order(n);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return pts[a].y < pts[b].y; });
    vi rev(n);
    rep(i, 0, n) rev[order[i]] = i;
    vvi ans(n, vi(n));

    vector<pair<P, pii>> events;
    rep(i, 0, n){
        rep(j, 0, n){
            if(i == j) continue;
            events.push_back({pts[j] - pts[i], {i, j}});
        }
    }
    sort(all(events));

    int start = 0;
    vi use(n);
    while(start < sz(events)){
        int end = start;
        vi cur;
        while(end < sz(events) && !(events[start].f < events[end].f) && !(events[end].f < events[start].f)){
            auto [dir, p] = events[end];
            auto [i1, i2] = p;
            if(rev[i2] > rev[i1]) {
                swap(order[rev[i1]], order[rev[i2]]);
                swap(rev[i1], rev[i2]);
            }
            for(int i : {i1, i2}) {
                if(!use[i]) {
                    cur.pb(i);
                    use[i] = true;
                }
            }
            end++;
        }
        for(int i : cur){
            ans[i][rev[i]]++;
            ans[i][n - 1 - rev[i]]++;
            use[i] = false;
        }

        start = end;
    }
    rep(i, 0, n){
        rep(j, 1, n){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
