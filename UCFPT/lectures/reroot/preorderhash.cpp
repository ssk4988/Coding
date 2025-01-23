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

const int mod = 1e9+7;
const int base = 998244353;
vl pw;
using state = pair<int, ll>; // {subsize, hash}

// append b to a
state add(state a, state b) {
    return {a.first + b.first, (a.second * pw[b.first] % mod + b.second) % mod};
}

vl solve_brute(vvi adj) {
    int n = sz(adj);

    auto dfs = [&](int u, int p, vi &a, auto &&dfs) -> void {
        a.push_back(u);
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, a, dfs);
        }
    };
    vl ans;
    rep(start, 0, n){
        vi ord;
        dfs(start, -1, ord, dfs);
        ll h = 0;
        for(int i : ord) {
            h = (h * base + i+1) % mod;
        }
        ans.push_back(h);
    }
    return ans;
}

vl solve_prefsuff(vvi adj) {
    int n = sz(adj);
    vector<state> dp(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> state {
        dp[u] = {1, u+1};
        for(int v : adj[u]) if(v != p) {
            dp[u] = add(dp[u], dfs(v, u, dfs));
        }
        return dp[u];
    };
    dfs(0, -1, dfs);
    vector<state> reroot(n);
    auto dfs1 = [&](int u, int p, state parent_dp, auto &&dfs1) -> void {
        vector<pair<int, state>> child;
        if(p != -1) {
            child.emplace_back(p, parent_dp);
        }
        for(int v : adj[u]) if(v != p) {
            child.emplace_back(v, dp[v]);
        }
        sort(all(child));
        auto pref(child), suff(child);
        rep(i, 1, sz(pref)){
            pref[i].second = add(pref[i-1].second, pref[i].second);
        }
        reroot[u] = add({1, u+1}, pref.back().second);
        for(int i = sz(suff)-2; i >= 0; i--){
            suff[i].second = add(suff[i].second, suff[i+1].second);
        }
        rep(i, 0, sz(child)) {
            int v = child[i].first;
            if(v == p) continue;
            state cur = {1, u+1};
            if(i) cur = add(cur, pref[i-1].second);
            if(i+1 < sz(child)) cur = add(cur, suff[i+1].second);
            dfs1(v, u, cur, dfs1);
        }
    };
    dfs1(0, -1, state{0, 0}, dfs1);
    vl ans(n);
    rep(i, 0, n) ans[i] = reroot[i].second;
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    cout << n << endl;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    rep(i, 0, n) sort(all(adj[i]));
    pw.push_back(1);
    rep(i, 0, n+5) {
        pw.push_back(pw.back() * base % mod);
    }
    vl hash_brute = solve_brute(adj);
    for(auto x : hash_brute) {
        cout << x << " ";
    }
    cout << endl;
    vl hash_prefsuff = solve_prefsuff(adj);
    for(auto x : hash_prefsuff) {
        cout << x << " ";
    }
    cout << endl;
    assert(hash_brute == hash_prefsuff);
    return 0;
}
