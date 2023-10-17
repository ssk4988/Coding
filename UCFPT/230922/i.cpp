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
const double eps = 1e-9;
template <class T>
bool cmp(T x, T y)
{
    // if(fabs(x - y) <= eps) return true;
    return x <= y + eps;
}

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const
    {
        // cout << "comparing " << *this << " " << p << nL;
        // if (fabs(x - p.x) < eps)
        //     return cmp(y, p.y);
        // return cmp(x, p.x);
        return tie(x,y) < tie(p.x,p.y);
    }
    bool operator==(P p) const
    {
        // cout << "equating " << *this << " " << p << nL;
        return (*this - p).dist() < eps;
    }
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

typedef Point<double> P;
double segDist(P &s, P &e, P &p)
{
    if (s == e)
        return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}
template <class P>
bool onSegment(P s, P e, P p)
{
    return segDist(s, e, p) <= eps;
}

template <class P>
vector<P> segInter(P a, P b, P c, P d)
{
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a))
        s.insert(a);
    if (onSegment(c, d, b))
        s.insert(b);
    if (onSegment(a, b, c))
        s.insert(c);
    if (onSegment(a, b, d))
        s.insert(d);
    return {all(s)};
}

template <class S, class T>
auto lower(const S &s, const T &x, bool strict = 0)
{
    auto it = strict ? s.lower_bound(x) : s.upper_bound(x);
    return it == begin(s) ? end(s) : prev(it);
}
template <class S, class T>
auto higher(const S &s, const T &x, bool strict = 0)
{
    return strict ? s.upper_bound(x) : s.lower_bound(x);
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    // using P = Point<double>;
    vector<pair<P, P>> lines(n);
    rep(i, 0, n)
    {
        cin >> lines[i].f.x >> lines[i].f.y >> lines[i].s.x >> lines[i].s.y;
    }
    P st;
    cin >> st.x >> st.y;
    double v;
    cin >> v;
    P fs, fe;
    cin >> fs.x >> fs.y >> fe.x >> fe.y;
    lines.pb({fs, fe});
    double vf;
    cin >> vf;
    // vector<P> inters;
    map<P, int> rl;
    vector<set<P>> online(n + 1);
    // cout << "read input" << nL;
    rep(i, 0, n)
    {
        rep(j, i + 1, n + 1)
        {
            // vector<P> inters =
            // cout << i << " " << j << nL;
            auto inters = segInter(lines[i].f, lines[i].s, lines[j].f, lines[j].s);
            // cout << i << " " << j << " " << sz(inters) << nL;
            // assert(sz(inters) <= 1);
            // if(sz(inters) < 1) continue;
            for (auto inter : inters)
            {
                // cout << "found inter: " << inter << nL;
                if (rl.count(inter) == 0)
                {
                    rl[inter] = sz(rl);
                    // cout << "added point"
                    //      << " " << inter << nL;
                }
                else
                {
                    // auto pre = rl.find(inter)->f;
                    // cout << "already added: " << pre << " " << (pre == inter) << nL;
                }

                online[i].insert(inter);
                online[j].insert(inter);
            }
        }
    }
    auto addPoint = [&](P &p) -> void
    {
        if (!rl.count(p))
        {
            rl[p] = sz(rl);
        }
        rep(i, 0, n + 1)
        {
            if (onSegment(lines[i].f, lines[i].s, p))
                online[i].insert(p);
        }
    };
    // addPoint(fs);
    // addPoint(fe);
    addPoint(st);
    rep(i, 0, n + 1){
        addPoint(lines[i].f);
        addPoint(lines[i].s);
    }
    map<int, P> rrl;
    for (auto [key, val] : rl)
    {
        rrl[val] = key;
    }
    // for (auto p : online[0])
    // {
    //     cout << p << nL;
    // }
    vector<vector<pair<int, double>>> adj(sz(rl));
    rep(i, 0, n){
        auto v = online[i];
        for(auto p : v){
            // cout << i << " " << p << nL;
        }
        for(auto it = v.begin(); it != v.end(); it = next(it)){
            auto p1 = *it;
            if(it != v.begin()){
                auto p2 = *prev(it);
                adj[rl[p1]].pb({rl[p2], (p1 - p2).dist()});
                adj[rl[p2]].pb({rl[p1], (p1 - p2).dist()});
            }
        }
    }
    // for (auto [p, idx] : rl)
    // {
    //     rep(i, 0, n)
    //     {
    //         if (online[i].count(p) == 0)
    //             continue;
    //         auto it = lower(online[i], p, 1);
    //         if (it != online[i].end())
    //         {
    //             adj[idx].pb({rl[*it], (*it - p).dist()});
    //             // cout << p << " " << *it << nL;
    //         }
    //         it = higher(online[i], p, 1);
    //         if (it != online[i].end())
    //         {
    //             adj[idx].pb({rl[*it], (*it - p).dist()});
    //             // cout << p << " " << *it << nL;
    //         }
    //     }
    //     // cout << "inter point: " << p << nL;
    // }
    vector<double> dist(sz(rl), 1e10);
    dist[rl[st]] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, rl[st]});
    vi visited(sz(rl));

    while (!pq.empty())
    {
        auto [d, cur] = pq.top();
        pq.pop();
        if (visited[cur])
            continue;
        visited[cur] = true;
        // cout << rrl[cur] << " " << d << nL;
        for (auto [nex, w] : adj[cur])
        {
            if (!visited[nex] && dist[nex] - eps > dist[cur] + w)
            {
                dist[nex] = dist[cur] + w;
                pq.push({dist[nex], nex});
            }
        }
    }
    bool found = false;
    double ans = 1e10;
    for (auto p : online[n])
    {
        // cout << "on line: " << p << " " << (p - fs).dist() << " " << dist[rl[p]] << nL;
        if ((p - fs).dist() * v + eps >= dist[rl[p]] * vf)
        {
            // cout << p << nL;
            ans = min(ans, (p - fs).dist() / vf);
        }
    }
    // for (auto [p, val] : rl)
    // {
    //     cout << p << " " << dist[val] << nL;
    // }
    if (ans == 1e10)
    {
        cout << -1 << nL;
    }
    else
    {
        cout << fixed << setprecision(8) << ans << nL;
    }

    return 0;
}
