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

typedef Point<ld> P;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<P> pts(n);
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
        pts[i].x = x;
        pts[i].y = y;
    }
    ld area = 0;
    P center(0, 0);
    rep(i, 0, n){
        int j = (i+1) % n;
        ld cross = pts[i].x * pts[j].y - pts[j].x * pts[i].y;
        area += cross;
        center.x += (pts[i].x + pts[j].x) * cross;
        center.y += (pts[i].y + pts[j].y) * cross;
    }
    area /= 2;
    center = center / (6 * area);
    area = fabs(area);
    if (center.x < mnX - 1e-9 && addX <= mnX)
        cout << "unstable" << "\n";
    else if (center.x > mxX + 1e-9 && addX >= mxX)
        cout << "unstable" << "\n";

    // Always works.
    else if (addX >= mnX && addX <= mxX && center.x >= mnX - 1e-9 && center.x <= mxX + 1e-9)
        cout << "0 .. inf" << "\n";

    // This is the fun part.
    else
    {

        // Centroid x is within the base.
        if (center.x >= mnX - 1e-9 && center.x <= mxX + 1e-9)
        {

            // Hanging point off to the right.
            if (addX > mxX)
            {
                ll w = (ll)((mxX - center.x) / (addX - mxX) * area + 1 - 1e-9);
                if (w > 0)
                    cout << "0 .. " << w << "\n";
                else
                    cout << "unstable" << "\n";
            }

            // Hanging point not off the right.
            else
            {

                ll w = (ll)((center.x - mnX) / (mnX - addX) * area + 1 - 1e-9);
                if (w > 0)
                    cout << "0 .. " << w << "\n";
                else
                    cout << "unstable" << "\n";
            }
        }

        // Centroid x is to the left.
        else if (center.x < mnX - 1e-9)
        {

            // Hanging poing off the right.
            if (addX > mxX)
            {

                ll loww = (ll)((mnX - center.x) / (addX - mnX) * area + 1e-9);
                ll highw = (ll)((mxX - center.x) / (addX - mxX) * area + 1 - 1e-9);
                cout << loww + " .. " + highw << "\n";
            }

            // Hanging point not off the right.
            else
            {
                ll w = (ll)((mnX - center.x) / (addX - mnX) * area + 1e-9);
                cout << w + " .. inf" << "\n";
            }
        }

        // Centroid x is to the right.
        else
        {

            // Hanging point to the left.
            if (addX < mnX)
            {
                ll loww = (ll)((center.x - mxX) / (mxX - addX) * area + 1e-9);
                ll highw = (ll)((center.x - mnX) / (mnX - addX) * area + 1 - 1e-9);
                cout << loww + " .. " + highw << "\n";
            }

            // Not to the left.
            else
            {
                ll w = (ll)((center.x - mxX) / (mxX - addX) * area + 1e-9);
                cout << w + " .. inf" << "\n";
            }
        }
    }

    return 0;
}
