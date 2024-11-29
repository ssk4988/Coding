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

int use[1 << 20 + 5];

void solve() {
    int h, g; cin >> h >> g;
    int n = 1 << h;
    vi a(n);
    vvi merged(n);
    rep(i, 1, n) {
        cin >> a[i];
        merged[i].pb(a[i]);
    }
    ll ans = 0;
    vi fin(1 << g);
    for(int i = n-1; i > 0; i--){
        if(i * 2 + 1 < n){
            vi res(sz(merged[i]) + sz(merged[2 * i + 1]));
            merge(all(merged[i]), all(merged[2 * i + 1]), begin(res));
            swap(res, merged[i]);
            res = vi(sz(merged[i]) + sz(merged[2 * i]));
            merge(all(merged[i]), all(merged[2 * i]), begin(res));
            swap(res, merged[i]);
        }
        if(i < (1 << g)){
            int mx = -1;
            if(i * 2 + 1 < (1 << g)) mx = max({mx, fin[i * 2], fin[i * 2 + 1]});
            auto it = upper_bound(all(merged[i]), mx);
            assert(it != end(merged[i]));
            fin[i] = *it;
            use[fin[i]] = true;
            ans += fin[i];
            merged[i].erase(it);
        }
    }
    cout << ans << "\n";
    for(int i = n-1; i > 0; i--) {
        if(!use[a[i]]) cout << i << " ";
        else use[a[i]] = false;
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }
    
    return 0;
}
