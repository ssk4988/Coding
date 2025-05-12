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
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vvi adj(n);
    rep(it, 0, 2) {
        vii st;
        st.push_back({int(1e9+1), -1});
        rep(i, 0, n) {
            while(st.back().f <= a[i]) st.pop_back();
            if(sz(st) > 1)
            adj[it ? (n-1-i) : i].push_back(it ? (n-1-st.back().s) : st.back().s);
            st.push_back({a[i], i});
        }
        reverse(all(a));
    }
    vi dp(n, -1);
    auto go = [&](int u, auto &&go) -> int {
        int &ans = dp[u];
        if(ans != -1) return ans;
        ans = 1;
        for(int v : adj[u]) {
            ans = max(ans, 1+ go(v, go));
        }
        return ans;
    };
    int ans = 0;
    rep(i, 0, n) {
        ans = max(ans, go(i, go));
    }
    cout << ans << "\n";

    
    return 0;
}
