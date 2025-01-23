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
    string s; cin >> s;
    int n = 0;
    int idx = 0;
    int pref = 0;
    bool wrap = false;
    rep(i, 0, sz(s)-1) {
        pref += s[i] == '(' ? 1 : -1;
        if(pref == 0) wrap = true;
    }
    if(wrap) s = "(" + s + ")";
    vvi child;
    auto bd = [&](int p, auto &&bd) -> void {
        int u = n;
        n++;
        child.resize(n);
        idx++;
        if(p != -1) child[p].pb(u);
        while(s[idx] == '(') bd(u, bd);
        idx++;
    };    
    bd(-1, bd);
    map<pii, pii> dp;
    // check wrap
    vi wlen(100000);
    for(int w = 1, p = 1; w < sz(wlen); w *= 10, p++) wlen[w] = p;
    rep(i, 1, sz(wlen)) wlen[i] = max(wlen[i], wlen[i-1]);
    // node, prefix length until now = length used in this subtree
    auto go = [&](int u, int p, auto &&go) -> pii {
        if(dp.count({u, p})) return dp[{u, p}];
        rep(len, 1, 15) {
            int startw = wlen[p + len];
            int endw = len - 2 - startw;
            if(endw < startw) continue;
            int cur = p + len;
            for(int v : child[u]) {
                auto [a, b] = go(v, cur, go);
                cur = a;
            }
            if (wlen[cur] <= endw) 
                return dp[{u, p}] = {cur, len};
        }
        assert(false);
    };
    string res;
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        auto [ans, len] = go(u, p, go);
        int startw = wlen[p + len];
        int endw = len - 2 - startw;
        res += to_string(p + len);
        res += ",";
        res += to_string(ans);
        res += ":";
        int cur = p + len;
        for(int v : child[u]) {
            dfs(v, cur, dfs);
            auto [a, b] = go(v, cur, go);
            cur = a;
        }
    };
    int ans = 0;
    vi v = wrap ? child[0] : vi{0};
    int len;
    for(int u : v) {
        dfs(u, ans, dfs);
        tie(ans, len) = go(u, ans, go);

    }
    cout << res << "\n";
    
    return 0;
}
