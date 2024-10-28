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
    int n; cin >> n;
    vvi ws(101);
    ll base = 0;
    rep(i, 0, n){
        int p, w; cin >> p >> w;
        ws[p].pb(w);
        if(p == 100) base += w;
    }
    vd best(2e5 + 1e4);
    best[0] = 1;
    rep(p, 0, 100){
        sort(all(ws[p]));
        reverse(all(ws[p]));
        int cnt = 3 + 100.0 / (100.0 - p);
        rep(i, 0, min(sz(ws[p]), cnt)) {
            int w = ws[p][i];
            for(int j = sz(best) - w - 1; j >= 0; j--){
                best[j+w] = max(best[j+w], best[j] * p / 100.0);
            }
        }
    }
    ld ans = base;
    rep(i, 0, sz(best)) ans = max(ans, (base + i) * best[i]);
    cout << fixed << setprecision(8) << ans << "\n";
    
    return 0;
}
