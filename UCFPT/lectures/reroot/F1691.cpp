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

const ll mod = 1e9+7;
ll modpow(ll b, ll p) {
    ll ans = 1;
    for(; p; b = b * b % mod, p /= 2)
        if (p&1) (ans *= b) %= mod;
    return ans;
}

struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = sz(t); i < n + 1; i++) {
    int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod,
      inv * t[i - 1].inv_fact % mod});
  }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
    t[n - k].inv_fact % mod;
}

int n, k;

using state = array<ll, 3>;

state add(state a, state b) {
    auto [ans1, activate1, sub1] = a;
    auto [ans2, activate2, sub2] = b;
    ll sub3 = sub1 + sub2;
    ll activate3 = (activate1 - C(sub2, k)) % mod;
    ll ans3 = (ans1 + ans2) % mod;
    return {ans3, activate3, sub3};
}

state rem(state a, state b) {
    auto [ans3, activate3, sub3] = a;
    auto [ans2, activate2, sub2] = b;
    ll sub1 = sub3 - sub2;
    ll activate1 = (activate3 + C(sub2, k)) % mod;
    ll ans1 = (ans3 - ans2) % mod;
    return {ans1, activate1, sub1};
}

state finalize(state a) {
    auto [ans, activate, sub] = a;
    activate = (C(sub, k) + activate) % mod;
    (ans += activate * sub) %= mod;
    return {ans, activate, sub};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k;
    vvi adj(n);
    C(n+5, k+5);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<state> dp(n), dp_final(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u] = {0, 0, 1};
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = add(dp[u], dp_final[v]);
        }
        dp_final[u] = finalize(dp[u]);
    };
    dfs(0, -1, dfs);
    vector<state> reroot(n);
    auto dfs1 = [&](int u, int p, state parent_dp, auto &&dfs1) -> void {
        state cur = dp[u];
        if(p != -1) cur = add(cur, parent_dp);
        reroot[u] = finalize(cur);
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u, finalize(rem(cur, dp_final[v])), dfs1);
        }
    };
    dfs1(0, -1, {0, 0, 0}, dfs1);
    
    ll ans = 0;
    rep(i, 0, n) {
        (ans += reroot[i][0]) %= mod;
    }
    cout << (ans + mod) % mod << "\n";

    return 0;
}
