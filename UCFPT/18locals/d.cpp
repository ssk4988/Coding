#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

template<class T>
struct Point{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y=0) : x(x), y(y){}
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T p) const { return P(x * p, y * p); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
};

using P = Point<ll>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    P c; ll r; cin >> c.x >> c.y >> r;
    P q; ll s; cin >> q.x >> q.y >> s;
    // c = c * 2;
    // q = q * 2;
    // r *= 2;
    // s *= 2;
    ll lx = q.x, rx = q.x + s, by = q.y, uy = q.y + s;

    bool intersects = false;
    // upper line
    if(lx <= c.x && c.x <= rx && c.y == uy + r){
        intersects = true;
    }
    // botttom line
    if(lx <= c.x && c.x <= rx && c.y == by - r){
        intersects = true;
    }
    // left line
    if(by <= c.y && c.y <= uy && c.x == lx - r){
        intersects = true;
    }
    // right line
    if(by <= c.y && c.y <= uy && c.x == rx + r){
        intersects = true;
    }
    ll r2 = r * r;
    P bl(lx, by), br(rx, by), tl(lx, uy), tr(rx, uy);
    // bottom left curve
    if((c - bl).dist2() == r2 && c.x <= lx && c.y <= by) intersects = true;
    // bottom right curve
    if((c - br).dist2() == r2 && rx <= c.x && c.y <= by) intersects = true;
    // top left curve
    if((c - tl).dist2() == r2 && c.x <= lx && uy <= c.y) intersects = true;
    // top right curve
    if((c - tr).dist2() == r2 && rx <= c.x && uy <= c.y) intersects = true;
    if(intersects){
        cout << 1 << "\n";
        return 0;
    }

    bool inside = false;
    // vertical bar
    if(lx <= c.x && c.x <= rx && by - r <= c.y && c.y <= uy + r){
        inside = true;
    }
    // horizontal bar
    if(by <= c.y && c.y <= uy && lx - r <= c.x && c.x <= rx + r){
        inside = true;
    }
    // bottom left curve
    if((c - bl).dist2() <= r2) inside = true;
    // bottom right curve
    if((c - br).dist2() <= r2) inside = true;
    // top left curve
    if((c - tl).dist2() <= r2) inside = true;
    // top right curve
    if((c - tr).dist2() <= r2) inside = true;
    if(inside){
        cout << 2 << "\n";
        return 0;
    }
    cout << 0 << "\n";
}
