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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vii ps;
        rep(i, 0, n){
            ps.pb({a[i], i});
        }
        sort(all(ps));
        int l = 0, r = n-1;
        bool works = true;
        int mn = n, mx = -1;
        for(auto [v, i] : ps) {
            if(mn <= i - v || i + v <= mx) works = false;
            mn = min(mn, i), mx = max(mx, i);
            l = max(l, i - v + 1);
            r = min(r, i + v - 1);
        }
        if(works && l <= r) {
            cout << (r-l+1) << "\n";
        } else cout << 0 << "\n";
    }
    
    return 0;
}
