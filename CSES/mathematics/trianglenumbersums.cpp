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

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const ll lim = 1e12+10;
    vl tri;
    tri.push_back(0);
    while(tri.back() < lim) {
        ll v = sz(tri);
        tri.push_back(v * (v+1) / 2);
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ll n; cin >> n;
        int ans = 3;
        int p = sz(tri)-1;
        auto it = lower_bound(all(tri), n);
        rep(i, 0, sz(tri)) {
            while(p >= 0 && tri[i] + tri[p] > n) p--;
            if(p >= 0 && tri[i] + tri[p] == n) {
                ans = 2;
                break;
            }
        }
        if(it != end(tri) && *it == n) ans = 1;
        cout << ans << "\n";
    }
    
    return 0;
}
