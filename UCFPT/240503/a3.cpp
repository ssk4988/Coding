#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pdd = pair<ld, ld>;
using vii = vector<pii>;
using vdd = vector<pdd>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vdd x(n), v(n);
    rep(i, 0, n){
        cin >> x[i].first >> x[i].second >> v[i].first >> v[i].second;
    }
    const ld inf = LDBL_MAX;
    auto score = [&](ld t) -> ld {
        ld minx = LDBL_MAX, miny = LDBL_MAX, maxx = LDBL_MIN, maxy = LDBL_MAX;
        rep(i, 0, n){
            ld px = x[i].first + v[i].first * t;
            ld py = 
        }
    };
    
    return 0;
}
