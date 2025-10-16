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

const int mod = 998244353;
void solve() {
    int n, m; cin >> n >> m;
    vvi good(n, vi(n, 1));
    rep(_, 0, m) {
        int i, x; cin >> i >> x; i--, x--;
        good[i][x] = 0;
    }
    vvi ex(n, vi(n, n));
    for(int i = n-1; i >= 0; i--) {
        rep(j, 0, n) {
            if(!good[i][j]) {
                ex[i][j] = i;
                continue;
            }
            ex[i][j] = i+1;
            if(i+1 < n && j+1 < n) ex[i][j] = ex[i+1][j+1];
        }
    }
    vector dp(n+1, vector(n+1, vi(2))); // {idx, previous start, zero at beginning in previous}
    // if zero at beginning, then first guy in next split cant be 1 more than current
    // if used single 1, dont allow zero at nxt-1 if len > 1
    dp[0][0][0] = 1;
    rep(at, 0, n) {
        rep(prv, 0, at) {
            rep(beg, 0, 2) {
                rep(nxt, at+1, n+1) {
                    int len = nxt - at;
                    rep(zero, at, nxt) {
                        int first = len - (zero - at);
                        if(beg && at - prv == first) continue;
                        // if(single && len > 1 && zero == nxt-1) continue;
                        if(ex[zero][0] < nxt) continue;
                        if(zero > at && ex[at][len - (zero - at)] < zero) continue;
                        (dp[nxt][at][zero == at] += dp[at][prv][beg]) %= mod;
                        // cerr << at << " " << nxt << " " << zero << " cont " << dp[at] << endl;
                    }
                }
            }
        }
    }
    vvi pos;
    auto dfs = [&](int at, int single, vi cur, auto &&dfs) -> void {
        if(at == n) {
            pos.pb(cur);
            return;
        }
        rep(nxt, at+1, n+1) {
            int len = nxt - at;
            rep(zero, at, nxt) {
                if(single && len > 1 && zero == nxt-1) continue;
                if(ex[zero][0] < nxt) continue;
                if(zero > at && ex[at][len - (zero - at)] < zero) continue;
                vi cur2(cur);
                rep(i, at, nxt) {
                    if(i < zero) cur2.pb(len - (zero - at) + (i-at));
                    else cur2.pb(i-zero);
                }
                cur2.pb(-1);
                dfs(nxt, len==1, cur2, dfs);
            }
        }
    };
    dfs(0, 0, vi{}, dfs);
    sort(all(pos));
    for(auto &v : pos){
        for(auto x : v) cerr << x << " ";
        cerr << endl;
    }
    cerr << sz(pos) << endl;
    ll ans = (dp[n][0] + dp[n][1]) % mod;
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
