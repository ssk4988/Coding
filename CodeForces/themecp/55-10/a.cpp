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
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vi pref{0};
    rep(i, 0, n) pref.pb(pref.back() ^ a[i]);
    vl sm(sz(a));
    partial_sum(all(a), begin(sm));
    sm.insert(begin(sm), 0);
    map<int, set<int>> odd, even;
    rep(i,0,sz(pref)) {
        (i&1 ? odd : even)[pref[i]].insert(i);
    }
    rep(i, 0, q) {
        int l, r; cin >> l >> r;
        l--;
        if(sm[r]-sm[l] == 0){
            cout << "0\n";
            continue;
        }
        if(pref[l] != pref[r]) {
            cout << "-1\n";
            continue;
        }
        if((r-l)&1) {
            cout << "1\n";
            continue;
        }
        auto &v = (l&1 ? even : odd)[pref[l]];
        auto it = v.upper_bound(l);
        auto it1 = v.lower_bound(r);
        int ans = 3;
        if(it != end(v) && *it < r) {
            int l1 = *it;
            if(sm[l1] - sm[l] == 0) {
                ans = min(ans, 1);
            }
            ans = min(ans, 2);
        }
        if(it1 != begin(v) && *prev(it1) > l) {
            int r1 = *prev(it1);
            if(sm[r] - sm[r1] == 0) {
                ans = min(ans, 1);
            }
            ans = min(ans, 2);
        }
        if(ans == 3) ans = -1;
        cout << ans << "\n";
    }
    
    return 0;
}
