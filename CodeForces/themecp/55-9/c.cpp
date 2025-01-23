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
const int N = 1e5 + 100;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vvi divs(N);
    rep(i, 1, N){
        for(int j = i; j < N; j += i) divs[j].pb(i);
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        int mx = *max_element(all(a));
        const ll inf = 1e18;
        vector dp(20, vl(mx+1, inf));
        for(int x : a) dp[0][x] = ll(n) * x;
        vl cnt(mx+1);
        for(int x : a) for(int d : divs[x]) cnt[d]++;
        vvi trans(mx+1);
        vi c(mx+1);
        rep(i, 1, mx+1){
            reverse(all(divs[i]));
            for(int d : divs[i]) {
                c[d] = cnt[d];
                for(int d2 : divs[i]) {
                    if(d2 == d || d2 % d != 0) continue;
                    c[d] -= c[d2];
                }
                if(c[d]) 
                    trans[i].pb(d);
            }
            reverse(all(divs[i]));
        }
        rep(i, 0, sz(dp)-1){
            rep(j, 0, sz(dp[i])) {
                if(dp[i][j] == inf) continue;
                for(int d : trans[j]) {
                    // if(cnt[d]) {
                        dp[i+1][d] = min(dp[i+1][d], dp[i][j] + ll(d-j) * (n - (i+1)));
                    // }
                }
            }
        }
        ll ans = inf;
        rep(i, 0, sz(dp)) ans = min(ans, *min_element(all(dp[i])));
        cout << ans << "\n";
    }
    
    return 0;
}
