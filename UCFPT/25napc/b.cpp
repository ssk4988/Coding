#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()



struct pt {
    ll x, y;
    pt(ll x = 0, ll y= 0): x(x), y(y) {}
    pt operator+(pt p) { return pt(x + p.x, y + p.y); }
    pt operator-(pt p) { return pt(x - p.x, y - p.y); }
    pt operator*(ll c) { return pt(x * c, y * c); }
    pt operator/(ll c) { return pt(x / c, y / c); }
    ll cross(pt p) { return x * p.y - y * p.x; }
    ll cross(pt p, pt q) { return (p-*this).cross(q-*this); }
    ll dot(pt p) { return x*p.x + y*p.y; }
    pt perp() { return pt(-y, x); }
    double dist() { return sqrtl(x*x + y*y); }
};

struct ptd {
    double x, y;
    ptd(double x = 0, double y = 0): x(x), y(y) {}
    ptd operator+(ptd p) { return ptd(x + p.x, y + p.y); }
    ptd operator-(ptd p) { return ptd(x - p.x, y - p.y); }
    ptd operator*(double c) { return ptd(x * c, y * c); }
    ptd operator/(double c) { return ptd(x / c, y / c); }
    double cross(ptd p) { return x * p.y - y * p.x; }
    double cross(ptd p, ptd q) { return (p-*this).cross(q-*this); }
    double dot(ptd p) { return x*p.x + y*p.y; }
    ptd perp() { return ptd(-y, x); }
    double dist() { return sqrtl(x*x + y*y); }
};

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if(d == 0) return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}


typedef ptd  P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
    vector<P> res;
    rep(i, 0, sz(poly)) {
        P cur = poly[i], prev = i ? poly[i-1] : poly.back();
        bool side = s.cross(e, cur) < 0;
        if(side != (s.cross(e, prev) < 0))
            res.push_back(lineInter(s, e, cur, prev).second);
        if(side)
            res.push_back(cur);
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    int n, W, H; cin >> n >> W >> H;
    int B = W * 2;
    n += 2;
    vi h(n);
    vector<ptd> line(n);
    rep(i, 1, n-1) {
        cin >> h[i];
    }
    rep(i, 0, n){
        line[i].x = i;
        line[i].y = h[i];
    }
    vector<vector<double>> inter(n, vector<double>(1 << B));
    vector<vector<double>> aunion(n, vector<double>(1 << B));
    rep(i, 0, n) {
        rep(mask, 1, 1 << B) {
            if(!(mask&1)) continue;
            int minx = i - W, maxx = i+W, miny = h[i] - H, maxy = h[i] + H;
            rep(j, 0, B) {
                if(i - j < 0) continue;
                if(((mask >> j)&1) == 0) continue;
                int k = i-j;
                minx = max(minx, k - W);
                miny = max(miny, h[k] - H);
                maxy = min(maxy, h[k] + H);
                maxx = min(maxx, k + W);
            }
            double area = 0;
            if(miny < maxy && minx < maxx) {
                vector<ptd> poly;
                for(int i = min(n-1, maxx); i >= max(0, minx); i--) {
                    poly.push_back(line[i]);
                }
                poly.push_back(poly.back());
                poly.back().y = 0;
                poly.push_back(poly[0]);
                poly.back().y = 0;
                poly = polygonCut(poly, ptd(minx, 0), ptd(minx, 1));
                poly = polygonCut(poly, ptd(maxx, 1), ptd(maxx, 0));
                poly = polygonCut(poly, ptd(1, miny), ptd(0, miny));
                poly = polygonCut(poly, ptd(0, maxy), ptd(1, maxy));
                rep(i, 0, sz(poly)) {
                    area += poly[i].cross(poly[(i+1)%sz(poly)]);
                }
                area /= 2;
                // cerr << "minx " << minx << " maxx " << maxx << " miny " << miny << " maxy " << maxy << endl;
                // for(auto p : poly) {
                //     cerr << p.x << " " << p.y << ",";
                // }
                // cerr << endl;
                // cerr << "inter " << i << " " << mask << " " << area << endl;
            }
            inter[i][mask] = area;
        }
    }
    rep(i, 0, n) {
        rep(mask, 1, 1 << B) {
            if(!(mask&1)) continue;
            double area = 0;
            for(int sub = mask; sub; sub = (sub-1)&mask) {
                int lbit = __lg(sub & -sub);
                int sub1 = sub >> lbit;
                int j = i - lbit;
                if(j < 0) continue;
                // cerr << i << " " << mask << " " << j << " " << sub1 << " " << lbit << endl;
                if(__builtin_popcount(sub)&1) area += inter[j][sub1];
                else area -= inter[j][sub1];
            }
            // if(area)
            //     cerr << "union area: " << i << " " << mask << " " << area << endl;
            aunion[i][mask] = area;
        }
    }
    int P = B-1;
    // cerr << "P=" << P << " " << (1 <<P) << endl;
    vector dp(n, vector(n+1, vector<double>(1 << P, -1)));
    int allmask = (1 << P)-1;
    auto go = [&](int idx, int left, int prv, auto &&go) -> double {
        if(idx == n || left == 0) return 0;
        auto &ans = dp[idx][left][prv];
        if(ans != -1) return ans;
        ans = go(idx+1, left, (prv*2)&allmask, go); // dont use this guy
        // use this guy
        if(idx > 0 && idx+1<n)
        {
            int nxt = (prv*2+1);
            double newarea = aunion[idx][nxt];
            double oldarea = 0;
            if(prv) {
                int lbit = __lg(prv & -prv);
                int prv1 = prv >> lbit;
                int idx1 = idx-1 - lbit;
                oldarea = aunion[idx1][prv1];
            }
            ans = max(ans, go(idx+1, left-1, nxt&allmask, go) + newarea - oldarea);
        }
        // cerr << "dp " << idx << " " << left << " " << prv << " " << ans << endl;
        return ans;
    };
    vector<double> ans(n+1);
    rep(i, 1, n-1) {
        ans[i] = go(0, i, 0, go);
        cout << fixed << setprecision(10) << ans[i] << "\n";
    }

    return 0;
}
