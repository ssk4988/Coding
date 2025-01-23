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

void solve() {
    int n; cin >> n;
    vi a(n);
    ll ans = ll(n) * (n+1) / 2;
    rep(i, 0, n) {
        cin >> a[i]; a[i]--;
    }
    rep(i, 0, 12) {
        map<int, int> qmap, umap;
        int pref = 0;
        umap[pref]++;
        rep(j, 0, n) {
            pref += (a[j] >= i ? 1 : -1);
            if(a[j] == i) {
                for(auto [key, val] : umap) qmap[key] += val;
                umap.clear();
            }
            ans -= qmap[pref];
            umap[pref]++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
