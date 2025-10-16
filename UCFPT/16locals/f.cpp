#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define f first
#define s second
using P = pair<double,double>;
const double eps = 1e-6;
double dist(P a, P b) {
    return sqrt((a.f - b.f) * (a.f-b.f) + (a.s-b.s) * (a.s-b.s));
}
bool cmp(P a, P b) {
    if(dist(a, b) <= eps) return false;
    return a < b;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vector<P> pts(n);
        rep(i, 0, n) {
            cin >> pts[i].f >> pts[i].s;
        }
        int ans = 0;
        rep(i, 0, n) {
            rep(j, 0, n) {
                if(i == j) continue;
                P mid = {(pts[i].f + pts[j].f)/2, (pts[i].s + pts[j].s)/2};
                bool has = false;
                rep(k, 0, n) {
                    if(dist(pts[k], mid) > eps) continue;
                    has = true;
                }
                if(!has) continue;
                P other = {mid.f + (pts[j].s - pts[i].s), mid.s - (pts[j].f - pts[i].f)};
                has = false;
                rep(k, 0, n) {
                    if(dist(pts[k], other) > eps) continue;
                    has = true;
                }
                ans += has;
                // if(has) {
                //     cerr << pts[i].f << "," << pts[i].s << " " << pts[j].f << "," << pts[j].s << " " << mid.f << "," << mid.s << " " << other.f << "," << other.s << endl;
                // }
            }
        }
        cout << "Set #" << (cn+1) << ": " << ans << "\n";
        cout << "\n";
    }
    return 0;
}
