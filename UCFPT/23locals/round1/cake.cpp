#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;
using ld = long double;

#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vpi cs(n);
    rep(i, 0, n){
        cin >> cs[i].f >> cs[i].s;
    }
    auto cross = [&](int i, int j)->int{
        return -(cs[i].f * cs[j].s - cs[i].s * cs[j].f);
    };
    int best = 0;
    int tot = 0;
    rep(i, 0, n){
        tot += cross(i, (i + 1) % n);
    }
    rep(i, 0, n){
        int pre = (i + 1) % n;
        int area = cross(i, pre);
        rep(pts, 3, n + 1){
            int j = (pre + 1) % n;
            area += cross(pre, j);
            int area1 = area + cross(j, i);
            best = max(best, min(area1, tot - area1));
            pre = j;
        }
    }
    // cout << tot << "\n";
    cout << fixed << setprecision(1) << (ld(abs((tot - best) - best)) / 2) << "\n";
}
