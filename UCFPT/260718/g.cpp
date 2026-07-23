#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct P {
    ll x, y;
    P operator+(P p) const {
        return P{x + p.x, y + p.y};
    }
    P operator-(P p) const {
        return P{x - p.x, y - p.y};
    }
    ll cross(P p) {
        return x * p.y - y * p.x;
    }
    ll cross(P p, P q) {
        return (p - *this).cross(q - *this);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
    rep(i, 0, n) {
        cin >> pts[i].x >> pts[i].y;
    }
    vi ans(n+1);
    rep(i, 0, n) {
        rep(j, 0, i) {
            rep(k, 0, j) {
                int inside = 0;
                rep(l, 0, n) {
                    ll val;
                    int cnt = 0;
                    val = pts[i].cross(pts[j], pts[l]);
                    if(val == 0) continue;
                    cnt += val > 0;
                    val = pts[j].cross(pts[k], pts[l]);
                    if(val == 0) continue;
                    cnt += val > 0;
                    val = pts[k].cross(pts[i], pts[l]);
                    if(val == 0) continue;
                    cnt += val > 0;
                    if(cnt == 0 || cnt == 3) inside++;
                }
                ans[inside]++;
            }
        }
    }
    rep(i, 0, n-2) {
        cout << ans[i] << "\n";
    }

    return 0;
}
