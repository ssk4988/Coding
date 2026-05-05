#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

const ll mod = 1'000'000'007;

ll modpow(ll b, ll e) {
    ll res = 1;
    for (; e; e /= 2, (b *= b) %= mod)
        if (e&1) (res *= b) %= mod;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    vector<int> p(n, -1);
    vector<int> depth(n);
    vector<vector<int>> child(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        child[p[i]].push_back(i);
        depth[i] = depth[p[i]]+1;
    }


    vector<ll> e_leave(n);
    for (int i = n-1; i >= 0; i--) {
        if (child[i].empty()) {
            e_leave[i] = 1;
            continue;
        }
        ll tot = 0;
        for (int j : child[i]) (tot += e_leave[j]) %= mod;
        (tot *= modpow(ssize(child[i]), mod-2)) %= mod;
        e_leave[i] = (1 + tot)*(depth[i]+1)%mod*modpow(depth[i], mod-2)%mod;
    }
    
    vector<ll> tot_sub_leave(n);
    for (int i = 1; i < n; i++) (tot_sub_leave[p[i]] += e_leave[i]) %= mod;

    vector<ll> e_enter(n);
    vector<ll> avg_unc_dist(n);
    vector<ll> root_dist(n);
    for (int i = 1; i < n; i++) {
        e_enter[i] = (ssize(child[p[i]])
                        + (tot_sub_leave[p[i]]- e_leave[i])
                        + (ssize(child[p[i]])-1)*avg_unc_dist[p[i]])%mod;
        root_dist[i] = (root_dist[p[i]] + e_enter[i])%mod;
        avg_unc_dist[i] = (avg_unc_dist[p[i]] + e_enter[i])*depth[i]%mod*modpow(depth[i]+1, mod-2)%mod;
    }

    const int LG = 18;
    
    struct Pof {
        int p;
        int len, depth;
        ll bot_dist, avg_dist; // dist to get anywhere higher

        Pof operator*(const Pof& o) const {
            if (len == 0) return o;
            if (o.len == 0) return *this;
            ll o_exp = o.len*modpow(o.depth + 1, mod-2)%mod*o.avg_dist%mod; // given we start at o or higher exp to end above o
            return Pof {
                o.p,
                len + o.len,
                depth,
                (bot_dist + o_exp)%mod,
                (((avg_dist + o_exp)*len%mod + o.avg_dist*o.len%mod)%mod*modpow(len + o.len, mod-2))%mod
            };
        }
    };

    vector<vector<Pof>> dp(LG, vector<Pof>(n, Pof{}));

    // for (int i = 0; i < n; i++) cout << p[i] << " ";
    // cout << "\n";

    for (int i = 1; i < n; i++) {
        dp[0][i] = { p[i], 1, depth[i], e_leave[i], e_leave[i] };
        for (int j = 0; j < LG-1; j++) {
            // cout << dp[j][i].p << endl;
            dp[j+1][i] = dp[j][i]*dp[j][dp[j][i].p];
        }
    }

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        
        Pof res{};
        int xx = x, yy = y;
        for (int j = LG-1; j >= 0; j--) {
            if (depth[xx] > depth[yy] && (((depth[xx] - depth[yy])>>j)&1)) {
                res = res*dp[j][xx];
                xx = dp[j][xx].p;
            }
            if (depth[yy] > depth[xx] && (((depth[yy] - depth[xx])>>j)&1)) {
                yy = dp[j][yy].p;
            }
        }
        for (int j = LG-1; j >= 0; j--) {
            if (dp[j][xx].p == dp[j][yy].p) continue;
            res = res*dp[j][xx];
            xx = dp[j][xx].p;
            yy = dp[j][yy].p;
        }
        if (xx != yy) {
            res = res*dp[0][xx];
            xx = dp[0][xx].p;
            yy = dp[0][yy].p;
        }
        ll tot;
        if (xx == x) {
            tot = (root_dist[y] - root_dist[x]) % mod;
        } else {
            tot = (res.bot_dist + avg_unc_dist[xx] + (root_dist[y] - root_dist[xx]))%mod;
        }
        cout << (tot%mod + mod)%mod << "\n";
    }

    return 0;
}
