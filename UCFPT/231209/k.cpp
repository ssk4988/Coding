#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using pll = pair<ll, ll>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define pb push_back

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const {return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const {return tie(x,y)==tie(p.x,p.y);}
    P operator+(P p) const {return P(x + p.x, y + p.y); }
    P operator-(P p) const {return P(x - p.x, y - p.y); }
    P operator*(T d) const {return P(x * d, y * d); }
    P operator/(T d) const {return P(x / d, y / d); }
    T dot(P p) const {return x * p.x + y*p.y; }
    T cross(P p) const { return x* p.y - y * p.x; }
    T cross(P a, P b) const {return (a - *this).cross(b - *this);}
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); }
    P perp() const {return P(-y, x); }
    P normal() const {return perp().unit(); }
    P rotate(double a) const {
        return P(x * cos(a) - y*sin(a), x * sin(a) + y * cos(a)); 
    }
    bool side() const {
        return (y > 0 || (y == 0 && x >= 0));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template <class P> bool onSegment(P s, P e, P p){
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

using P = Point<ll>;
bool cmpDir(P a, P b) {
    if(a.side() != b.side()) return a.side() > b.side();
    return a.cross(b) > 0;
}

inline ll nc2(ll n){
    return n * (n - 1) / 2;
}

#define f first
#define s second
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<pair<P, P>> lines(n);
        set<P> ps;
        rep(i, 0, n){
            cin >> lines[i].f.x >> lines[i].f.y >> lines[i].s.x >> lines[i].s.y;
            ps.insert(lines[i].f);
            ps.insert(lines[i].s);
        }
        ll ans = 0;
        for(P ref : ps){
            map<P, pll, decltype(&cmpDir)> bucket(&cmpDir); // ends, bases
            // cout << "reference point: " << ref << "\n";
            for(auto [p1, p2] : lines) {
                if(onSegment(p1, p2, ref) && !(ref == p1 || ref == p2)){
                    bucket[p1 - ref].s++;
                    bucket[p2 - ref].s++;
                }
                else if(p1 == ref){
                    bucket[p2 - ref].f++;
                }
                else if(p2 == ref){
                    bucket[p1 - ref].f++;
                }
            }
            vector<P> keys;
            vector<pll> vals;
            vl pref, pref2, frq;
            for(auto [key, val] : bucket){
                keys.pb(key);
                vals.pb(val);
                frq.pb(val.s);
                pref.pb(val.f);
                // cout << key << " " << val.f << " " << val.s << "\n";
                pref2.pb(nc2(val.f));
                if(sz(pref) > 1) pref.back() += pref[sz(pref) - 2];
                if(sz(pref2) > 1) pref2.back() += pref2[sz(pref2) - 2];
            }
            int j = 0;
            rep(i, 0, sz(keys)){
                j = max(i + 1, j);
                while(j < sz(keys) && keys[i].cross(keys[j]) > 0){
                    j++;
                }
                if(j >= sz(keys) || keys[i].cross(keys[j]) != 0) continue;
                // cout << "range " << i << " " << j << "\n";
                // if(j < sz(keys)){
                    ll cnt = pref[j-1] - pref[i], exc = pref2[j-1] - pref2[i];
                    ll cont = frq[i] * (nc2(cnt) - exc);
                    // cout << frq[i] << " " << cnt << " " << exc << "\n";
                    ans += cont;
                    cnt = 0, exc = 0;
                    if(i){
                        cnt += pref[i-1];
                        exc += pref2[i-1];
                    }
                    cnt += pref.back() - pref[j];
                    exc += pref2.back() - pref2[j];
                    cont = frq[i] * (nc2(cnt) - exc);
                    // cout << frq[i] << " " << cnt << " " << exc << "\n";
                    ans += cont;
                // }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
