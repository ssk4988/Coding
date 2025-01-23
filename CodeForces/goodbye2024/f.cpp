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

// dp[i][c1] = max(max over c(dp[i-1][c] + freq[i][c] * ext[i-1] + freq[i-1][c1] * ext[i]), dp[i-1][c1] + freq[i][c1] * ext[i-1] + freq[i-1][c1] * ext[i] + ext[i] * ext[i+1])
// dp[i][c1] = freq[i-1][c1] * ext[i] + max(max over c(dp[i-1][c] + freq[i][c] * ext[i-1]), dp[i-1][c1] + freq[i][c1] * ext[i-1] + ext[i] * ext[i+1])

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<map<int, ll>> freq(n);
    vl ext(n);
    rep(i, 0, n){
        rep(j, 0, m){
            int v; cin >> v; if(v == -1) ext[i]++;
            else freq[i][v-1]++;
        }
    }
    vl natural(n);
    rep(i, 0, n-1){
        for(auto [c, v] : freq[i]) {
            if(freq[i+1].count(c)) natural[i] += freq[i][c] * freq[i+1][c];
        }
    }
    vl dp(k);
    set<pll> cmp;
    rep(i, 0, k){
        cmp.insert({dp[i], i});
    }
    ll floor = -1e18;
    auto fix = [&](int key) {
        if(dp[key] < floor) {
            cmp.erase({dp[key], key});
            dp[key] = floor;
            cmp.insert({dp[key], key});
        }
    };
    rep(i, 1, n){
        ll mx = -1e18;
        {
            auto it = prev(end(cmp));
            mx = max(mx, it->f - ext[i] * ext[i-1]);
        }
        for(auto [key, val] : freq[i]){
            fix(key);
            mx = max(mx, dp[key] - ext[i] * ext[i-1] + val * ext[i-1]);
            cmp.erase({dp[key], key});
            dp[key] += val * ext[i-1];
            cmp.insert({dp[key], key});
        }
        floor = max(mx, floor);
        for(auto [key, val] : freq[i-1]) {
            fix(key);
            cmp.erase({dp[key], key});
            dp[key] += freq[i-1][key] * ext[i];
            cmp.insert({dp[key], key});
        }
    }
    ll ans = -1e18;
    rep(i, 0, k) fix(i), ans = max(ans, dp[i]);
    rep(i, 0, n) ans += natural[i];
    rep(i, 1, n) ans += ext[i] * ext[i-1];
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}

