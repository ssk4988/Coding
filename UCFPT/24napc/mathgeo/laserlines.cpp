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
    while (true)
    {
        vector<P> pts;
        {
            int x, y;
            cin >> x >> y;
            pts.push_back(P{x, y});
            if (x == 0 && y == 0)
                break;
        }
        while (true)
        {
            int x, y;
            cin >> x >> y;
            if (x == 0 && y == 0)
                break;
            pts.push_back(P{x, y});
        }
        int n = sz(pts);
        vector<vector<P>> lines;
        rep(i, 0, n){
            rep(j, 0, i){
                P s = pts[i], e = pts[j];
                P dif = e - s;
                vector<P> line;
                bool bad = false;
                rep(k, 0, n){
                    if(s.cross(pts[k], e) != 0) continue;
                    if(dif.dot(pts[k] - s) > dif.dist2() || dif.dot(pts[k] - s) < 0) bad = true;
                    else line.pb(pts[k]);
                }
                if(bad || sz(line) <= 2) continue;
                sort(all(line));
                lines.pb(line);
            }
        }
        if(sz(lines) == 0){
            cout << "No lines were found\n";
            continue;
        }
        cout << "The following lines were found:\n";
        sort(all(lines));
        for(auto &line : lines){
            for(auto p : line){
                cout << "(" << setw(4) << p.x << "," << setw(4) << p.y << ")";
            }
            cout << "\n";
        }
    }

    return 0;
}
