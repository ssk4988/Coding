#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x)(int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ld = long double;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
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
    ld dist() const { return sqrt((ld) dist2()); }
    ld angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(ld a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); 
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ld> P;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
ld circlePoly(P c, ld r, vector<P> ps) {
    auto tri = [&](P p, P q) {
        auto r2 = r * r / 2;
        P d = q - p;
        auto a = d.dot(p) / d.dist2(), b = (p.dist2() - r * r) / d.dist2();
        auto det = a * a - b;
        if (det <= 0) return arg(p, q) * r2;
        auto s = max(ld(0.), -a-sqrt(det)), t = min(ld(1.), -a+sqrt(det));
        if(t < 0 || 1 <= s) return arg(p, q) * r2;
        P u = p + d * s, v = p + d * t;
        return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
    };
    auto sum = 0.0;
    rep(i,0,sz(ps))
        sum += tri(ps[i] - c, ps[(i+1)%sz(ps)] - c);
    return sum;
}


ld eps0 = 1e-7;
using Pl = Point<ll>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll r, dx, dy, cx, cy;
    ld p; cin >> r >> dx >> dy >> cx >> cy >> p;
    while(cx > 0) cx -= dx;
    while(cx < 0) cx += dx;
    while(cy > 0) cy -= dy;
    while(cy < 0) cy += dy;
    vector<ld> areas;
    auto rect = [&](ll i, ll j) -> bool {
        ll x = cx + dx * i;
        ll y = cy + dy * j;
        vector<P> ps;
        ps.push_back(P(ld(x), ld(y)));
        ps.push_back(P(ld(x + dx), ld(y)));
        ps.push_back(P(ld(x + dx), ld(y + dy)));
        ps.push_back(P(ld(x), ld(y + dy)));
        ld area = circlePoly(P(0, 0), ld(r), ps);
        if(area < eps0) return false;
        areas.push_back(area);
        return true;
    };
    // inside the circle
    auto check = [&](ll i, ll j) -> bool {
        ll x = cx + dx * i;
        ll y = cy + dy * j;
        vector<Pl> ps;
        ps.push_back(Pl((x), (y)));
        ps.push_back(Pl((x + dx), (y)));
        ps.push_back(Pl((x + dx), (y + dy)));
        ps.push_back(Pl((x), (y + dy)));
        for(auto &p : ps){
            if(p.dist2() > r * r) return false;
        }
        return true;
    };
    const int iter = 2005;
    rep(i, -iter, iter){
        ll j = 0;
        while(check(i, j)){
            areas.push_back(ld(dy * dx));
            j++;
        }
        while(rect(i, j)) j++;
        j = -1;
        while(check(i, j)){
            areas.push_back(ld(dy * dx));
            j--;
        }
        while(rect(i, j)) j--;
    }
    // cout << sz(areas) << "\n";
    sort(all(areas));
    // for(auto area : areas){
    //     cout << fixed << setprecision(8) << area << "\n";
    // }
    int cnt = 0;
    while(cnt < sz(areas)){
        if(areas[cnt] <= (p + eps0) * areas.back()){
            cnt++;
        }
        else break;
    }
    cout << cnt << "\n";

    return 0;
}